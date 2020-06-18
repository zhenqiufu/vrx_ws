
(cl:in-package :asdf)

(defsystem "multi_dp-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "motor_msgs" :depends-on ("_package_motor_msgs"))
    (:file "_package_motor_msgs" :depends-on ("_package"))
  ))