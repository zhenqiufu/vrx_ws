;; Auto-generated. Do not edit!


(when (boundp 'multi_dp::motor_msgs)
  (if (not (find-package "MULTI_DP"))
    (make-package "MULTI_DP"))
  (shadow 'motor_msgs (find-package "MULTI_DP")))
(unless (find-package "MULTI_DP::MOTOR_MSGS")
  (make-package "MULTI_DP::MOTOR_MSGS"))

(in-package "ROS")
;;//! \htmlinclude motor_msgs.msg.html


(defclass multi_dp::motor_msgs
  :super ros::object
  :slots (_stamp _rotation _alpha _alpha_deg _BalphaU _tau _u ))

(defmethod multi_dp::motor_msgs
  (:init
   (&key
    ((:stamp __stamp) (instance ros::time :init))
    ((:rotation __rotation) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:alpha __alpha) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:alpha_deg __alpha_deg) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:BalphaU __BalphaU) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:tau __tau) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:u __u) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _stamp __stamp)
   (setq _rotation __rotation)
   (setq _alpha __alpha)
   (setq _alpha_deg __alpha_deg)
   (setq _BalphaU __BalphaU)
   (setq _tau __tau)
   (setq _u __u)
   self)
  (:stamp
   (&optional __stamp)
   (if __stamp (setq _stamp __stamp)) _stamp)
  (:rotation
   (&optional __rotation)
   (if __rotation (setq _rotation __rotation)) _rotation)
  (:alpha
   (&optional __alpha)
   (if __alpha (setq _alpha __alpha)) _alpha)
  (:alpha_deg
   (&optional __alpha_deg)
   (if __alpha_deg (setq _alpha_deg __alpha_deg)) _alpha_deg)
  (:BalphaU
   (&optional __BalphaU)
   (if __BalphaU (setq _BalphaU __BalphaU)) _BalphaU)
  (:tau
   (&optional __tau)
   (if __tau (setq _tau __tau)) _tau)
  (:u
   (&optional __u)
   (if __u (setq _u __u)) _u)
  (:serialization-length
   ()
   (+
    ;; time _stamp
    8
    ;; float64[] _rotation
    (* 8    (length _rotation)) 4
    ;; float64[] _alpha
    (* 8    (length _alpha)) 4
    ;; float64[] _alpha_deg
    (* 8    (length _alpha_deg)) 4
    ;; float64[] _BalphaU
    (* 8    (length _BalphaU)) 4
    ;; float64[] _tau
    (* 8    (length _tau)) 4
    ;; float64[] _u
    (* 8    (length _u)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; time _stamp
       (write-long (send _stamp :sec) s) (write-long (send _stamp :nsec) s)
     ;; float64[] _rotation
     (write-long (length _rotation) s)
     (dotimes (i (length _rotation))
       (sys::poke (elt _rotation i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _alpha
     (write-long (length _alpha) s)
     (dotimes (i (length _alpha))
       (sys::poke (elt _alpha i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _alpha_deg
     (write-long (length _alpha_deg) s)
     (dotimes (i (length _alpha_deg))
       (sys::poke (elt _alpha_deg i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _BalphaU
     (write-long (length _BalphaU) s)
     (dotimes (i (length _BalphaU))
       (sys::poke (elt _BalphaU i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _tau
     (write-long (length _tau) s)
     (dotimes (i (length _tau))
       (sys::poke (elt _tau i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _u
     (write-long (length _u) s)
     (dotimes (i (length _u))
       (sys::poke (elt _u i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; time _stamp
     (send _stamp :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _stamp :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64[] _rotation
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _rotation (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _rotation i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _alpha
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _alpha (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _alpha i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _alpha_deg
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _alpha_deg (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _alpha_deg i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _BalphaU
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _BalphaU (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _BalphaU i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _tau
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _tau (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _tau i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _u
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _u (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _u i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get multi_dp::motor_msgs :md5sum-) "887cc1d691af56b569d609397c3a5014")
(setf (get multi_dp::motor_msgs :datatype-) "multi_dp/motor_msgs")
(setf (get multi_dp::motor_msgs :definition-)
      "time stamp
float64[] rotation
float64[] alpha
float64[] alpha_deg
float64[] BalphaU
float64[] tau
float64[] u
")



(provide :multi_dp/motor_msgs "887cc1d691af56b569d609397c3a5014")


