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

import io
import math
import sys
import os
import re
import pexpect

# special import for run_p2 (pattern)
import subprocess
import difflib

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
    s = s.replace(' ', '\\s+').replace('\n', '\\s+')
    return f'\\s*{s}\\s*'


def run_p1(binary):
    """Run part-1 Olympic Judge Average"""
    logger = setup_logger()
    status = []
    error_values = (
        [None, 'error: you must give at least three scores'],  # 0 args, too few
        ['1', 'error: you must give at least three scores'],  # 1 arg, too few
        [
            '1',
            '2',
            'error: you must give at least three scores',
        ],  # 2 args, too few
    )
    values = (
        [5.0, 5.0, 5.0, 5.0],  # all same
        [0.0, 0.0, 0.0, 0.0],  # zeroes
        [1.0, 2.0, 3.0, 2.0],  # 3 increasing
        [3.0, 2.0, 1.0, 2.0],  # 3 decreasing
        [5.1, 8.7, 9.0, 2.6, 1.9, 5.46667],  # 5 floats
        # all 24 permutations of 3 5 7 8
        [3.0, 5.0, 7.0, 8.0, 6.0],
        [3.0, 5.0, 8.0, 7.0, 6.0],
        [3.0, 7.0, 5.0, 8.0, 6.0],
        [3.0, 7.0, 8.0, 5.0, 6.0],
        [3.0, 8.0, 5.0, 7.0, 6.0],
        [3.0, 8.0, 7.0, 5.0, 6.0],
        [5.0, 3.0, 7.0, 8.0, 6.0],
        [5.0, 3.0, 8.0, 7.0, 6.0],
        [5.0, 7.0, 3.0, 8.0, 6.0],
        [5.0, 7.0, 8.0, 3.0, 6.0],
        [5.0, 8.0, 3.0, 7.0, 6.0],
        [5.0, 8.0, 7.0, 3.0, 6.0],
        [7.0, 3.0, 5.0, 8.0, 6.0],
        [7.0, 3.0, 8.0, 5.0, 6.0],
        [7.0, 5.0, 3.0, 8.0, 6.0],
        [7.0, 5.0, 8.0, 3.0, 6.0],
        [7.0, 8.0, 3.0, 5.0, 6.0],
        [7.0, 8.0, 5.0, 3.0, 6.0],
        [8.0, 3.0, 5.0, 7.0, 6.0],
        [8.0, 3.0, 7.0, 5.0, 6.0],
        [8.0, 5.0, 3.0, 7.0, 6.0],
        [8.0, 5.0, 7.0, 3.0, 6.0],
        [8.0, 7.0, 3.0, 5.0, 6.0],
        [8.0, 7.0, 5.0, 3.0, 6.0],
        # minimum is duplicated, but should only be omitted once
        [3.0, 1.0, 1.0, 5.0, 2.0],
        # maximum is duplicated, but should only be omitted once
        [4.0, 2.0, 9.0, 9.0, 3.0, 5.33333],
    )
    for index, val in enumerate(error_values):
        test_number = index + 1
        logger.info('Test %d - %s', test_number, val)
        rv = _run_p1_error(binary, val)
        if not rv:
            logger.error(
                "Did not receive expected response for test %d.", test_number
            )
        status.append(rv)

    for index, val in enumerate(values):
        test_number = len(error_values) + index + 1
        logger.info('Test %d - %s', test_number, val)
        rv = _run_p1(binary, val)
        if not rv:
            logger.error(
                "Did not receive expected response for test %d.", test_number
            )
        status.append(rv)
    return status


def _run_p1_error(binary, values):
    logger = setup_logger()
    status = False
    if values[0] is None:
        proc = pexpect.spawn(binary, timeout=1)
    else:
        argument_strings = list(map(str, values[:-1]))
        proc = pexpect.spawn(binary, timeout=1, args=argument_strings)

    expected = values[-1]

    with io.BytesIO() as log_stream:
        proc.logfile = log_stream
        try:
            regex = expected.replace(' ', '\\s+')
            proc.expect(fr'(?i).*{regex}.*')
        except (
            pexpect.exceptions.TIMEOUT,
            pexpect.exceptions.EOF,
        ) as exception:
            logger.error(f'Expected: "{expected}"')
            logger.error('Could not find expected output.')
            logger.error(
                'Your output: "%s"', log_stream.getvalue().decode('utf-8')
            )
            logger.debug("%s", str(exception))
            logger.debug(str(proc))
            return status

        proc.expect(pexpect.EOF)
        proc.close()
        if proc.exitstatus == 0:
            logger.error("Expected: non-zero exit code.")
            logger.error(f'Exit code was {proc.exitstatus}.')
            logger.error("Program returned zero, but non-zero is required")
            logger.error(
                'Your output: "%s"', log_stream.getvalue().decode('utf-8')
            )
            return status
    status = True
    return status


def _run_p1(binary, values):
    """The actual test with the expected input and output"""
    logger = setup_logger()
    status = False
    argument_strings = list(map(str, values[:-1]))
    expected_float = values[-1]
    proc = pexpect.spawn(binary, timeout=1, args=argument_strings)
    # proc.logfile = sys.stdout.buffer

    with io.BytesIO() as log_stream:
        proc.logfile = log_stream
        try:
            match_index = proc.expect(
                r'(?i)\s*average\s*is\s*([-+]?[0-9]+[.]?[0-9]*([eE][-+]?[0-9]+)?)\s*'
            )

            token = proc.match.group(1).decode("utf-8")
            actual = float(token)
            # 1% tolerance
            if not math.isclose(expected_float, actual, rel_tol=0.01):
                logger.error(
                    'actual numeric output is %f, which does not equal %f',
                    actual,
                    expected_float,
                )
                return status

        except (
            pexpect.exceptions.TIMEOUT,
            pexpect.exceptions.EOF,
        ) as exception:
            logger.error('Expected: "average is ' + str(expected_float) + '"')
            logger.error('Could not find expected output.')
            logger.error(
                'Your output: "%s"', log_stream.getvalue().decode('utf-8')
            )
            logger.debug("%s", str(exception))
            logger.debug(str(proc))
            return status

        proc.expect(pexpect.EOF)
        proc.close()
        if proc.exitstatus != 0:
            logger.error("Expected: zero exit code.")
            logger.error(f'Exit code was {proc.exitstatus}.')
            logger.error("Program returned non-zero, but zero is required")
            logger.error(
                'Your output: "%s"', log_stream.getvalue().decode('utf-8')
            )
            return status

    status = True
    return status

def run_p2(binary):
    """Run part-2"""
    # This is a straight up diff. No need for Expect.
    logger = setup_logger()
    status = []
    cmd = binary
    # logger.debug('clang format: %s', cmd)
    proc = subprocess.run(
        [cmd],
        capture_output=True,
        shell=True,
        timeout=2,
        check=False,
        text=True,
    )
    output = proc.stdout.split("\n")

    correct_output = "*||||||||||||||||||||||\n-*|||||||||||||||||||||\n--*||||||||||||||||||||\n---*|||||||||||||||||||\n----*||||||||||||||||||\n-----*|||||||||||||||||\n------*||||||||||||||||\n-------*|||||||||||||||\n--------*||||||||||||||\n---------*|||||||||||||\n----------*||||||||||||\n-----------*|||||||||||\n------------*||||||||||\n-------------*|||||||||\n--------------*||||||||\n---------------*|||||||\n----------------*||||||\n-----------------*|||||\n------------------*||||\n-------------------*|||\n--------------------*||\n---------------------*|\n".split(
        "\n"
    )

    diff = difflib.context_diff(
        correct_output,
        output,
        "Correct Output",
        "Student Program's Output",
        n=3,
    )
    diff = list(diff)
    if len(diff) > 0:
        logger.warning("The program's output does not match what was expected.")
        logger.warning("Expected\n{}".format("\n".join(correct_output)))
        logger.warning("Your output\n{}".format("\n".join(output)))

        logger.warning(
            "The diff between your program's output and the expected output is:"
        )
        logger.warning("\n".join(diff))
        # print('\n'.join(output))
        status.append(False)
    else:
        logger.info("Program output matches expected output.")
        status.append(True)
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
