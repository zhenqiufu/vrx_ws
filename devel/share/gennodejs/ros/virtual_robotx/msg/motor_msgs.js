// Auto-generated. Do not edit!

// (in-package virtual_robotx.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class motor_msgs {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.stamp = null;
      this.rotation = null;
      this.alpha = null;
      this.alpha_deg = null;
      this.BalphaU = null;
      this.tau = null;
      this.u = null;
    }
    else {
      if (initObj.hasOwnProperty('stamp')) {
        this.stamp = initObj.stamp
      }
      else {
        this.stamp = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('rotation')) {
        this.rotation = initObj.rotation
      }
      else {
        this.rotation = [];
      }
      if (initObj.hasOwnProperty('alpha')) {
        this.alpha = initObj.alpha
      }
      else {
        this.alpha = [];
      }
      if (initObj.hasOwnProperty('alpha_deg')) {
        this.alpha_deg = initObj.alpha_deg
      }
      else {
        this.alpha_deg = [];
      }
      if (initObj.hasOwnProperty('BalphaU')) {
        this.BalphaU = initObj.BalphaU
      }
      else {
        this.BalphaU = [];
      }
      if (initObj.hasOwnProperty('tau')) {
        this.tau = initObj.tau
      }
      else {
        this.tau = [];
      }
      if (initObj.hasOwnProperty('u')) {
        this.u = initObj.u
      }
      else {
        this.u = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type motor_msgs
    // Serialize message field [stamp]
    bufferOffset = _serializer.time(obj.stamp, buffer, bufferOffset);
    // Serialize message field [rotation]
    bufferOffset = _arraySerializer.float64(obj.rotation, buffer, bufferOffset, null);
    // Serialize message field [alpha]
    bufferOffset = _arraySerializer.float64(obj.alpha, buffer, bufferOffset, null);
    // Serialize message field [alpha_deg]
    bufferOffset = _arraySerializer.float64(obj.alpha_deg, buffer, bufferOffset, null);
    // Serialize message field [BalphaU]
    bufferOffset = _arraySerializer.float64(obj.BalphaU, buffer, bufferOffset, null);
    // Serialize message field [tau]
    bufferOffset = _arraySerializer.float64(obj.tau, buffer, bufferOffset, null);
    // Serialize message field [u]
    bufferOffset = _arraySerializer.float64(obj.u, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type motor_msgs
    let len;
    let data = new motor_msgs(null);
    // Deserialize message field [stamp]
    data.stamp = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [rotation]
    data.rotation = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [alpha]
    data.alpha = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [alpha_deg]
    data.alpha_deg = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [BalphaU]
    data.BalphaU = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [tau]
    data.tau = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [u]
    data.u = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.rotation.length;
    length += 8 * object.alpha.length;
    length += 8 * object.alpha_deg.length;
    length += 8 * object.BalphaU.length;
    length += 8 * object.tau.length;
    length += 8 * object.u.length;
    return length + 32;
  }

  static datatype() {
    // Returns string type for a message object
    return 'virtual_robotx/motor_msgs';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '887cc1d691af56b569d609397c3a5014';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    time stamp
    float64[] rotation
    float64[] alpha
    float64[] alpha_deg
    float64[] BalphaU
    float64[] tau
    float64[] u
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new motor_msgs(null);
    if (msg.stamp !== undefined) {
      resolved.stamp = msg.stamp;
    }
    else {
      resolved.stamp = {secs: 0, nsecs: 0}
    }

    if (msg.rotation !== undefined) {
      resolved.rotation = msg.rotation;
    }
    else {
      resolved.rotation = []
    }

    if (msg.alpha !== undefined) {
      resolved.alpha = msg.alpha;
    }
    else {
      resolved.alpha = []
    }

    if (msg.alpha_deg !== undefined) {
      resolved.alpha_deg = msg.alpha_deg;
    }
    else {
      resolved.alpha_deg = []
    }

    if (msg.BalphaU !== undefined) {
      resolved.BalphaU = msg.BalphaU;
    }
    else {
      resolved.BalphaU = []
    }

    if (msg.tau !== undefined) {
      resolved.tau = msg.tau;
    }
    else {
      resolved.tau = []
    }

    if (msg.u !== undefined) {
      resolved.u = msg.u;
    }
    else {
      resolved.u = []
    }

    return resolved;
    }
};

module.exports = motor_msgs;
