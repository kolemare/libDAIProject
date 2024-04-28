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
    "sp": "Sprinkler",
    "bp": "BP",
}

# Supported image sets
IMAGE_SETS = ["chess", "f4u_corsair"]

def build_command(args):
    # Initialize the command with the base command
    command = BASE_COMMAND.copy()

    # Add the operation type
    command.extend(['-op', OPERATIONS[args.operation]])

    if args.operation == "is":
        input_path1 = os.path.join('test', 'ImageSegmentation', args.image_set, f'{args.image_set}{args.image_num1}.jpg')
        input_path2 = os.path.join('test', 'ImageSegmentation', args.image_set, f'{args.image_set}{args.image_num2}.jpg')
        output_path1 = os.path.join('results', 'ImageSegmentation', 'local_evidence.jpg')
        output_path2 = os.path.join('results', 'ImageSegmentation', 'magnetizations.jpg')
        belief_path = os.path.join('results', 'ImageSegmentation', 'belief')
        command.extend(['-i1', input_path1, '-i2', input_path2, '-o1', output_path1, '-o2', output_path2, '-blf', belief_path])
    elif args.operation in ["bp", "sp"]:
        bpg_path = os.path.join('results', 'BipartiteGraph', 'bp_graph_')
        spfg_path = os.path.join('results', 'Sprinkler', 'sprinkler')
        command.extend(['-bpg', bpg_path, '-spfg', spfg_path])

    # Add all other options, use defaults if not provided by the user
    for key, value in DEFAULT_SETTINGS.items():
        command.extend([f'-{key}', getattr(args, key, None) or value])

    return command

def main():
    parser = argparse.ArgumentParser(description="Invoke libDAIApp with specified parameters.")
    parser.add_argument('operation', choices=OPERATIONS.keys(), help='Specify the operation to perform')

    args, unknown = parser.parse_known_args()

    if args.operation == "is":
        parser.add_argument('image_set', choices=IMAGE_SETS, help='Specify the image set to use')
        parser.add_argument('image_num1', type=str, help='Specify the first image number')
        parser.add_argument('image_num2', type=str, help='Specify the second image number')

    # Add other arguments that could be overridden by the user
    for setting, default in DEFAULT_SETTINGS.items():
        parser.add_argument(f'--{setting}', default=default, help=f'Set the {setting} parameter (default: {default})')

    # Re-parse all arguments now including optional ones
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