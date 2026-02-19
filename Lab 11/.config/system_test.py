#!/usr/bin/env python3
#
# Copyright 2021-2023 Michael Shafae
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
""" Check student's submission; requires the main file and the
    template file from the original repository. """
# pexpect documentation
#  https://pexpect.readthedocs.io/en/stable/index.html

# ex.
# .action/solution_check_p1.py  part-1 asgt

import io
import math
import sys
import os
import re
import pexpect

try:
    from assessment import csv_solution_check_make
except ImportError as e:
    from os.path import join, dirname

    sys.path.append(join(join(dirname(__file__), '..'), '.action'))
    from assessment import csv_solution_check_make
try:
    from logger import setup_logger
except ImportError as e:
    from os.path import join, dirname

    sys.path.append(join(join(dirname(__file__), '..'), '.action'))
    from logger import setup_logger
try:
    import lab_config as cfg
except ImportError as e:
    from os.path import join, dirname

    sys.path.append(join(join(dirname(__file__), '..'), '.config'))
    import lab_config as cfg

def regex_it(s):
    combine_white_space_regex = re.compile(r"\s+")
    s = combine_white_space_regex.sub(" ", s).strip()
    s = s.replace(' ', '\\s*').replace('\n', '\\s*')
    return f'(?i)\\s*{s}\\s*'

def run_p1(binary):
    """Run part-1"""
    logger = setup_logger()
    status = []
    error_values = ()
    values = [
        [11294.8, 1.28521],
    ]
    for index, val in enumerate(error_values):
        test_number = index + 1
        logger.info('Test %d - %s', test_number, val)
        rv = _run_p1_error(binary, val)
        if not rv:
            logger.error("Did not receive expected response for test %d.", test_number)
        status.append(rv)

    for index, val in enumerate(values):
        test_number = len(error_values) + index + 1
        logger.info('Test %d - %s', test_number, val)
        rv = _run_p1(binary, val)
        if not rv:
            logger.error("Did not receive expected response for test %d.", test_number)
        status.append(rv)
    return status

def _run_p1_error(binary, values):
    raise NotImplementedError

def _run_p1(binary, values):
    """The actual test with the expected input and output"""
    logger = setup_logger()
    status = False
    proc = pexpect.spawn(binary, timeout=1, args=[])
    # proc.logfile = sys.stdout.buffer

    with io.BytesIO() as log_stream:
        proc.logfile = log_stream
        try:
            regex = (r'(?i)\s*The\s*densest\s*state\s*is\s*District\s*of\s*Columbia\s*\('
                + r'([-+]?[0-9]+[.]?[0-9]*)\s*'
                + r'\)\s*'
                + r'The\s*sparsest\s*state\s*is\s*Alaska\s*\('
                + r'([-+]?[0-9]+[.]?[0-9]*)\s*'
                + r'\)\s*')

            match_index = proc.expect(regex)

            token = proc.match.group(1).decode("utf-8") 
            actual = float(token)
            expected = values[0]
            # 1% tolerance
            if not math.isclose(expected, actual, rel_tol=.01): 
                logging.error('actual numeric output is %f, which does not equal %f', actual, expected)
                return status

            token = proc.match.group(2).decode("utf-8") 
            actual = float(token)
            expected = values[1]
            # 1% tolerance
            if not math.isclose(expected, actual, rel_tol=.01): 
                logging.error('actual numeric output is %f, which does not equal %f', actual, expected)
                return status

        except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
            logger.error('Expected:\nThe densest state is District of Columbia (11294.8)\nThe sparsest state is Alaska (1.28521)')
            logger.error('Could not find expected output.')
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            logger.debug("%s", str(exception))
            logger.debug(str(proc))
            return status

        proc.expect(pexpect.EOF)
        proc.close()
        if proc.exitstatus != 0:
            logger.error("Expected: zero exit code.")
            logger.error(f'Exit code was {proc.exitstatus}.')
            logger.error("Program returned non-zero, but zero is required")
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            return status
        
    status = True
    return status

P2_VALUES = (
[5, 8, 2, 5,
'''You have 4 guesses left.
Enter a guess 1-10: 8
Too big!
You have 3 guesses left.
Enter a guess 1-10: 2
Too small!
You have 2 guesses left.
Enter a guess 1-10: 5
You won!
'''],

[9, 1, 2, 3, 4,
'''You have 4 guesses left.
Enter a guess 1-10: 1
Too small!
You have 3 guesses left.
Enter a guess 1-10: 2
Too small!
You have 2 guesses left.
Enter a guess 1-10: 3
Too small!
You have 1 guesses left.
Enter a guess 1-10: 4
Too small!
You lost!
'''],

[2, 9, 8, 7, 6,
'''You have 4 guesses left.
Enter a guess 1-10: 9
Too big!
You have 3 guesses left.
Enter a guess 1-10: 8
Too big!
You have 2 guesses left.
Enter a guess 1-10: 7
Too big!
You have 1 guesses left.
Enter a guess 1-10: 6
Too big!
You lost!
'''],

)

def run_p2(binary):
    """Run part-2"""
    logger = setup_logger()
    status = []
    error_values = []
    values = P2_VALUES

    for index, val in enumerate(values):
        test_number = len(error_values) + index + 1
        logger.info('Test %d - %s', test_number, val)
        rv = _run_p2(binary, val)
        if not rv:
            logger.error("Did not receive expected response for test %d.", test_number)
        status.append(rv)
    return status


def _run_p2(binary, values):
    logger = setup_logger()
    status = False

    argument = str(values[0])
    guesses = values[1:-1]
    expected_output = values[-1]

    proc = pexpect.spawn(binary, timeout=1, args=[argument])

    for guess in guesses:
        proc.sendline(str(guess))

    with io.BytesIO() as log_stream:
        proc.logfile = log_stream
        try:
            regex = expected_output.replace(' ', '\\s+').replace('\n', '\\s+')
            proc.expect(
                fr'(?i).*{regex}.*'
            )
        except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
            logger.error(f'Expected: "{expected_output}"')
            logger.error('Could not find expected output.')
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            logger.debug("%s", str(exception))
            logger.debug(str(proc))
            return status

        proc.expect(pexpect.EOF)
        proc.close()
        if proc.exitstatus != 0:
            logger.error("Expected: zero exit code.")
            logger.error(f'Exit code was {proc.exitstatus}.')
            logger.error("Program returned non-zero, but zero is required")
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            return status
    status = True
    return status


if __name__ == '__main__':
    cwd = os.getcwd()
    repo_name = os.path.basename(cwd)
    td = sys.argv[1]
    # print(td)
    if sys.argv[1] == 'part-1':
        part_config = cfg.lab['parts'][0]
    elif sys.argv[1] == 'part-2':
        part_config = cfg.lab['parts'][1]
    else:
        print(f'Error: {sys.argv[0]} no match.')
        sys.exit(1)

    _program_name = part_config['target']
    _files = part_config['src'].split() + part_config['header'].split()
    _do_format_check = part_config['do_format_check']
    _do_lint_check = part_config['do_lint_check']
    _do_unit_tests = part_config['do_unit_tests']
    _tidy_options = part_config['tidy_opts']
    _skip_compile_cmd = part_config['skip_compile_cmd']
    # There needs to be some magic here to figure out which due date to use.
    _lab_due_date = cfg.lab['mon_duedate'].isoformat()
    _run_func = locals()[part_config['test_main']]

    # Execute the solution check
    csv_solution_check_make(
        csv_key=repo_name,
        target_directory=td,
        program_name=_program_name,
        run=_run_func,
        files=_files,
        do_format_check=_do_format_check,
        do_lint_check=_do_lint_check,
        do_unit_tests=_do_unit_tests,
        tidy_options=_tidy_options,
        skip_compile_cmd=_skip_compile_cmd,
        lab_due_date=_lab_due_date,
    )
