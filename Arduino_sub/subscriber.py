import rospy
from std_msgs import Float32
# Ref used: https://www.programcreek.com/python/?code=PacktPublishing%2FLearning-Robotics-using-Python-Second-Edition%2FLearning-Robotics-using-Python-Second-Edition-master%2Fchapter_9_code%2Fchefbot_bringup%2Fscripts%2Ftwist_to_motors.py

# Main class
class HeatSubscriber():
	def __init__(self):

		# Init rospy
		rospy.init_node("heatSubscriber")
		nodename = rospy.get_name()

		# Subscriber
		rospy.Subscriber("heatSensor", Float32, self.messageReceive)

		self.delay = 100 # How many ticks to wait
		self.rate = 1e3 // self.delay
		self.timeout_ticks = 5000 # Ticks until timeout

	def spin(self):

		# Set up rates and delays
		r = rospy.Rate (self.rate)
		idle = rospy.Rate(10)
		then = rospy.Time.now()
		self.ticks_since_target = self.timeout_ticks

		# Main loop
		while not rospy.is_shutdown():
			# Continue with standard rate
			while not rospy.is_shutdown() and self.ticks_since_target < self.timeout_ticks:
				self.spinOnce()
				r.sleep()
			# If we don't receive any messages, slow down receiving
			idle.sleep()

	def spinOnce(self):
		self.ticks_since_target += 1
		# Publishing will go here

	def messageReceive (self, msg):
		print("Current heat: " + str(msg))
		# Eventually it would actually do something with the received message.


if __name__ == "__main__":
	# If not imported
	Heat_Sub = HeatSubscriber()
	Heat_Sub.spin()

