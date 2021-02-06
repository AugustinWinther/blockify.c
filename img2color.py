"""
Takes a folder of images and calculates the average color
of every image in the folder.

Results are saved in a clear text file, with the format:
"texture_path R G B"

Example:
/path/to/texture1.png 204 33 234
/path/to/texture2.png 24 44 144
...
"""

from os import listdir as folder
from os import path
from sys import argv as arguments

from PIL import Image

def main(arguments):
    # Check if arguments are passed from command line
    if len(arguments) < 3:
        print("Too few arguments!\n"
            "Script usage: python img2color.py <img dir> <output file>")
        quit()

    # Define passed arguments
    image_folder = arguments[1]
    output_file = arguments[2]

    # Check if image folder exists
    if not path.exists(image_folder):
        print("Image folder does not exist!")
        quit()

    # Create texture color index file
    result_file = open(output_file, "x")

    # Loop through textures and append to texture color index
    for image in folder(image_folder):
        image_path = str(image_folder) + str(image)
        image_color = get_avg_color(image_path)
        
        result_file.write(image_path)
        result_file.write(" ")
        result_file.write(str(image_color[0]))  # Red
        result_file.write(" ")
        result_file.write(str(image_color[1]))  # Green
        result_file.write(" ")
        result_file.write(str(image_color[2]))  # Blue
        result_file.write("\n")

# Function that returns the average color of a picture
def get_avg_color(image):
    with Image.open(image) as image:
        width  = image.size[0]
        height = image.size[1]
        pixel_count = width * height
        pixel = image.load()
        r_tot = 0
        g_tot = 0
        b_tot = 0
        
        # Loop through all pixels in picture
        for pixel_row in range(height):
            for pixel_column in range(width):
                r_tot += pixel[pixel_column, pixel_row][0]
                b_tot += pixel[pixel_column, pixel_row][2]
                g_tot += pixel[pixel_column, pixel_row][1]
        
        r_avg = round(r_tot / pixel_count) 
        g_avg = round(b_tot / pixel_count)
        b_avg = round(g_tot / pixel_count)

    # Return RGB tuple
    return (r_avg, g_avg, b_avg)

# If this scripts is run, do main(arguments)
if __name__ == '__main__':    
    main(arguments)