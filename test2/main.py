import pyautogui



import keyboard

# Define the function to be executed when the hotkey is pressed
def my_hotkey_function():
    print("Ctrl+Alt+K was pressed!")
    # Add your desired actions here, e.g., open a program, trigger a script, etc.

# Register the hotkey
# The first argument is the hotkey combination as a string
# The second argument is the function to call when the hotkey is pressed
keyboard.add_hotkey('ctrl+alt+k', my_hotkey_function)

# Keep the program running and listening for keyboard events
# This line is crucial for the hotkey listener to remain active
keyboard.wait()






print("hello world")