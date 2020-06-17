#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/joystick.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>

#define XBOX_TYPE_BUTTON 0x01
#define XBOX_TYPE_AXIS 0x02

#define XBOX_AXIS_LX 0x00 /* 杆X轴 */  // surge
#define XBOX_AXIS_LY 0x01 /* 杆Y轴 */  // sway
#define XBOX_AXIS_LT 0x02 /* 杆z轴 */  //左转
#define XBOX_AXIS_RT 0x05              //右转

#define XBOX_AXIS_VAL_UP -32767
#define XBOX_AXIS_VAL_DOWN 32767
#define XBOX_AXIS_VAL_LEFT -32767
#define XBOX_AXIS_VAL_RIGHT 32767

#define XBOX_AXIS_VAL_MIN -32767
#define XBOX_AXIS_VAL_MAX 32767
#define XBOX_AXIS_VAL_MID 0x00

typedef struct xbox_map {
  int time;

  int lx;
  int ly;

  int lt;
  int rt;

} xbox_map_t;

double joystick_cmd[4];
int len, type;
int xbox_fd;
xbox_map_t map;

int axis_value, button_value;
int number_of_axis, number_of_buttons;

int xbox_open(const char *file_name) {
  int xbox_fd;

  xbox_fd = open(file_name, O_RDONLY);
  if (xbox_fd < 0) {
    perror("open");
    return -1;
  }

  return xbox_fd;
}

int xbox_map_read(int xbox_fd, xbox_map_t *map) {
  int len, type, number, value;
  struct js_event js;

  len = read(xbox_fd, &js, sizeof(struct js_event));
  if (len < 0) {
    perror("read");
    return -1;
  }

  type = js.type;
  number = js.number;
  value = js.value;

  map->time = js.time;

  if (type == JS_EVENT_AXIS) {
    switch (number) {
      case XBOX_AXIS_LX:
        map->lx = value / 3.2767;
        break;

      case XBOX_AXIS_LY:
        map->ly = value / 3.2767;
        break;

      case XBOX_AXIS_LT:
        map->lt = value / 3.2767 + 10000;
        break;

      case XBOX_AXIS_RT:
        map->rt = value / 3.2767 + 10000;
        break;

      default:
        break;
    }
  } else {
    /* Init do nothing */
  }

  return len;
}

void xbox_close(int xbox_fd) {
  close(xbox_fd);
  return;
}

void getjoystick_cmd() {
  len = xbox_map_read(xbox_fd, &map);
  if (len < 0) {
    usleep(10);
    // continue;
  }

  // std::cout << "Time: " << map.time << "     X:" << map.lx
  //           << "      Y:" << map.ly << "       Z:" << map.lt <<
  //           std::endl;

  joystick_cmd[0] = map.lx;
  joystick_cmd[1] = map.ly;
  joystick_cmd[2] = map.lt;
  joystick_cmd[3] = map.rt;
}

int initial_joystick(const char *js_name) {
  memset(&map, 0, sizeof(xbox_map_t));
  // const char *js_name = "/dev/input/js1";
  xbox_fd = xbox_open(js_name);
  if (xbox_fd < 0) {
    return -1;
  }

  // while (1) {
  //   run2();

  //   // std::cout << "x force: " << joystick_cmd[0] << "    y: " <<
  //   // joystick_cmd[1]
  //   //           << "    z: " << joystick_cmd[2] << std::endl;

  //   // printf("\rTime:%8d  LX:%-6d LY:%-6d LT:%-6d ", map.time, map.lx,
  //   map.ly,
  //   //        map.lt);
  //   // fflush(stdout);
  // }

  return 0;
}

double getjysdcmd_x() { return joystick_cmd[0]; }
double getjysdcmd_y() { return joystick_cmd[1]; }
double getjysdcmd_z_l() { return joystick_cmd[2]; }
double getjysdcmd_z_r() { return joystick_cmd[3]; }
// double cmd[3];
// int main() {
//   std::cout << "hello word" << std::endl;

//   run();
//   cmd[0] = getjysdcmd_x();
//   cmd[1] = getjysdcmd_y();
//   cmd[2] = getjysdcmd_z();
//   std::cout << "x force: " << cmd[0] << "y: " << cmd[1] << "z: " << cmd[1]
//             << std::endl;
// }