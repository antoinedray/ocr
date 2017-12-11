import subprocess
import sys
import os

# Format of images
FORMAT = ".jpg"

# Get the path to the directory
DIR = os.path.dirname(os.path.realpath(__file__))

DATAFILE="data.txt"

# Custom colors for outputs
class bcolors:
    GREEN='\033[0;32m'
    NC='\033[0m' # No Color

if len(sys.argv) != 2:
    print("Invalid parameter, run 'python3 gen.py -h'")

else:
    if sys.argv[1] == "-gen":
        if os.path.exists(DATAFILE):
            os.remove(DATAFILE)
        subprocess.run(['./gen.sh'])

    elif sys.argv[1] == "-clean":
        os.remove(DATAFILE)
        for root, dirs, files in os.walk(DIR):
            for f in files:
                if f.endswith(FORMAT):
                    os.remove(f)
        print("[" + bcolors.GREEN + "SUCCESS" + bcolors.NC
                + "] Deleting all images previously generated")
    else:
        print("======== HELP ========")
        print("-gen : Generate the database")
        print("-clean : Clean the database")
