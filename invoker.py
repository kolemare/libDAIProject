import argparse
import subprocess
import os

# Define the base command and default settings
BASE_COMMAND = ['./libDAIApp']
DEFAULT_SETTINGS = {
    "J": "2.4",
    "thmin": "-3.0",
    "thmax": "3.2",
    "scale": "40.0",
    "pbg": "90.0",
    "method": "BP[updates=SEQMAX,maxiter=100,tol=1e-9,logdomain=0]",
    "maxiter": "100",
    "tol": "1e-9"
}

# Supported operations
OPERATIONS = {
    "is": "ImageSegmentation",
    "optionB": "OptionB",
    "optionC": "OptionC",
}

# Supported image sets
IMAGE_SETS = ["chess", "f4u_corsair"]

def build_command(args):
    # Initialize the command with the base command
    command = BASE_COMMAND.copy()

    # Add the operation type
    command.extend(['-op', OPERATIONS[args.operation]])

    # Determine the image set and image numbers
    if args.image_set not in IMAGE_SETS:
        raise ValueError(f"Unsupported image set: {args.image_set}. Supported sets are {IMAGE_SETS}.")
    img_num1, img_num2 = args.image_num1, args.image_num2

    # Add the input and output image paths
    input_path1 = os.path.join('test', 'ImageSegmentation', args.image_set, f'{args.image_set}{img_num1}.jpg')
    input_path2 = os.path.join('test', 'ImageSegmentation', args.image_set, f'{args.image_set}{img_num2}.jpg')
    output_path1 = os.path.join('results', 'ImageSegmentation', 'local_evidence.jpg')
    output_path2 = os.path.join('results', 'ImageSegmentation', 'magnetizations.jpg')
    belief_path = os.path.join('results', 'ImageSegmentation', 'beleif')
    
    command.extend(['-i1', input_path1, '-i2', input_path2, '-o1', output_path1, '-o2', output_path2, '-blf', belief_path])

    # Add all other options, use defaults if not provided by the user
    for key, value in DEFAULT_SETTINGS.items():
        command.extend([f'-{key}', getattr(args, key, None) or value])

    return command

def main():
    parser = argparse.ArgumentParser(description="Invoke libDAIApp with specified parameters.")
    parser.add_argument('operation', choices=OPERATIONS.keys(), help='Specify the operation to perform')
    parser.add_argument('image_set', choices=IMAGE_SETS, help='Specify the image set to use (chess or f4u_corsair)')
    parser.add_argument('image_num1', type=str, help='Specify the first image number (e.g., "1" for chess1)')
    parser.add_argument('image_num2', type=str, help='Specify the second image number (e.g., "3" for chess3)')
    
    # Add other arguments that could be overridden by the user
    for setting, default in DEFAULT_SETTINGS.items():
        parser.add_argument(f'--{setting}', help=f'Set the {setting} parameter (default: {default})')

    args = parser.parse_args()

    # Build the command based on the provided arguments
    command = build_command(args)

    # Run the command
    try:
        result = subprocess.run(command, check=True)
        print("Output:", result.stdout)
        print("Errors:", result.stderr)
    except subprocess.CalledProcessError as e:
        print("Error running command:", e)
        print("Return code:", e.returncode)
        print("Output:", e.stdout)
        print("Errors:", e.stderr)

if __name__ == "__main__":
    main()