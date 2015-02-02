import os

dir = '.'

out="target"
headers="header"

for root, dirs, files in os.walk(os.path.join(dir, headers), topdown=True):
    # Copying folder structure
    for dirname in dirs:
        in_out_folder = os.path.join(root.replace(headers, out), dirname)

        if not os.path.isdir(in_out_folder):
            print("Creating %s folder..." % in_out_folder)
            os.makedirs(in_out_folder)
