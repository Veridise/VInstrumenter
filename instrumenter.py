from argparse import Namespace, ArgumentParser

from tests.parse_tests import run_parse_tests

def main(args: Namespace):
    if args.regression:
        run_parse_tests(args)

if __name__ == "__main__":
    parser = ArgumentParser()
    parser.add_argument("--regression", help="option to run regression tests", action="store_true")

    args = parser.parse_args()
    main(args)
