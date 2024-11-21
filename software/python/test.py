import time
import bonic_cloud

# Initialize Bonic Cloud and get data reference
bonic_cloud.init()
data_ref = bonic_cloud.get_data_ref()

# Function to increment speed from 30 to 100 in steps of 10 every 10 seconds, and restart after 100
def push_speed_to_bonic_cloud():
    speed = 100
    data_ref.update({'speed': speed})
    
    while True:
        # Update the speed value in Bonic Cloud 
        data_ref.update({'speed': speed})
        print(f"Updated Bonic Cloud with speed: {speed}")

        # Increment speed by 10
        speed += 10

        # Reset speed to 30 if it exceeds 100
        if speed > 100:
            speed = 90

        # Wait for 10 seconds before pushing the next value
        if speed < 70:
         time.sleep(2)
        else:
         time.sleep(2)
            

# Start the function
push_speed_to_bonic_cloud()
