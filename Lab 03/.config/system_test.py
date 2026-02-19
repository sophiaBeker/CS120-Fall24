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
import logging
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
    s = s.replace(' ', '\\s+').replace('\n', '\\s+')
    return f'\\s*{s}\\s*'

def run_p1(binary):
    """Run part-1"""
    logger = setup_logger()
    status = []
    values = (
                (260, 76, 51, '2136.24', '1970.24'), # Dwayne Johnson
                (104, 56, 26, '1236.02', '1070.02'), # Simone Biles
                (212, 78, 41, '2000.27', '1834.27'), # Kobe Bryant
            )
    for index, val in enumerate(values):
        test_number = index + 1
        logger.info('Test %d - %s', test_number, val)
        rv = _run_p1(binary, val)
        if not rv:
            logger.error("Did not receive expected response for test %d.", test_number)
        status.append(rv)
    
    return status

def _run_p1(binary, values):
    """The actual test with the expected input and output"""
    logger = setup_logger()
    status = False
    proc = pexpect.spawn(binary, timeout=1)
    # proc.logfile = sys.stdout.buffer
    inputs = list(map(str, values[:3]))
    expected_man_str = values[3]
    expected_woman_str = values[4]
    
    # input to program

    i = 0
    try:
        proc.expect(regex_it('Enter weight in pounds:'))
    except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        logging.error('Expected: "Enter weight in pounds: "')
        logging.error('Could not find expected output.')
        logging.debug("%s", str(exception))
        logging.debug(str(proc))
        return status

    proc.sendline(inputs[i])
    i += 1

    try:
        proc.expect(regex_it('Enter height in inches:'))
    except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        logging.error('Expected: "Enter height in inches: "')
        logging.error('Could not find expected output.')
        logging.debug("%s", str(exception))
        logging.debug(str(proc))
        return status

    proc.sendline(inputs[i])
    i += 1

    try:
        proc.expect(regex_it('Enter age in years:'))
    except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        logging.error('Expected: "Enter age in years: "')
        logging.error('Could not find expected output.')
        logging.debug("%s", str(exception))
        logging.debug(str(proc))
        return status

    proc.sendline(inputs[i])
    i += 1

    # output from program

    # man
    try:
        # Match and extract any floating point number
        regex = r'(?i)\s*Man\s*:\s*([-+]?[0-9]+[.]?[0-9]*([eE][-+]?[0-9]+)?)\s*calories\s*per\s*day\s*'
        match_index = proc.expect(regex)
    except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        logging.error('Expected: "Man: %s calories per day"', expected_man_str)
        logging.error('Could not find expected output.')
        logging.debug("%s", str(exception))
        logging.debug(str(proc))
        return status
    token = proc.match.group(1).decode("utf-8") 
    actual = float(token)
    # 1% tolerance
    expected_float = float(expected_man_str)
    if not math.isclose(expected_float, actual, rel_tol=.01): 
        logging.error('logic error: actual numeric output for Man is %s, which is expected to be %s instead', token, expected_man_str)
        return status

    # woman
    try:
        # Match and extract the floating point number
        regex = r'(?i)\s*Woman\s*:\s*([-+]?[0-9]+[.]?[0-9]*([eE][-+]?[0-9]+)?)\s*calories\s*per\s*day\s*'
        match_index = proc.expect(regex)
    except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        logging.error('Expected: "Woman: %s calories per day"', expected_woman_str)
        logging.error('Could not find expected output.')
        logging.debug("%s", str(exception))
        logging.debug(str(proc))
        return status
    token = proc.match.group(1).decode("utf-8") 
    actual = float(token)
    # 1% tolerance
    expected_float = float(expected_woman_str)
    if not math.isclose(expected_float, actual, rel_tol=.01): 
        logging.error('logic error: actual numeric output for Woman is %s, which is expected to be %s instead', token, expected_woman_str)
        return status

    # EOF
    proc.expect(pexpect.EOF)
    proc.close()
    if proc.exitstatus == 0:
        status = True
    return status

# adapted from fall 2022 lab 07 part 1
def run_p2(binary):
    """Run part-2"""
    # status = True
    status = []
    values = (
                (1, 1, 2022, 1, 1, 2023, 365),
                (1, 1, 1984, 1, 1, 1985, 366),
                (12, 25, 1275, 12, 25, 2522, 455457),
                (9, 21, 2022, 10, 31, 1980, -15300),
                (10, 1, 79, 9, 23, 2022, 709658),
            )
    for index, val in enumerate(values):
        logging.info('Test %d - %s', index + 1, val)
        # status = status and _run_p1(binary, val)
        rv = _run_p2(binary, val)
        if not rv:
            logging.error("Did not receive expected response for test %d.", index + 1)
        status.append(rv)
    return status

def _run_p2(binary, values):
    """The actual test with the expected input and output"""
    status = False
    proc = pexpect.spawn(binary, timeout=1)
    # proc.logfile = sys.stdout.buffer
    values = list(map(str, values))
    
    i = 0
    try:
        proc.expect(
            r'(?i)\s*Enter\s*a\s*start\s*month:\s*'
        )
    except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        logging.error('Expected: "Enter a start month: "')
        logging.error('Could not find expected output.')
        logging.debug("%s", str(exception))
        logging.debug(str(proc))
        return status

    proc.sendline(values[i])
    i += 1

    try:
        proc.expect(
            r'(?i)\s*Enter\s*a\s*start\s*day:\s*'
        )
    except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        logging.error('Expected: "Enter a start day: "')
        logging.error('Could not find expected output.')
        logging.debug("%s", str(exception))
        logging.debug(str(proc))
        return status

    proc.sendline(values[i])
    i += 1

    try:
        proc.expect(
            r'(?i)\s*Enter\s*a\s*start\s*year:\s*'
        )
    except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        logging.error('Expected: "Enter a start year: "')
        logging.error('Could not find expected output.')
        logging.debug("%s", str(exception))
        logging.debug(str(proc))
        return status

    proc.sendline(values[i])
    i += 1

    try:
        proc.expect(
            r'(?i)\s*Enter\s*an\s*end\s*month:\s*'
        )
    except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        logging.error('Expected: "Enter an end month: "')
        logging.error('Could not find expected output.')
        logging.debug("%s", str(exception))
        logging.debug(str(proc))
        return status

    proc.sendline(values[i])
    i += 1
    
    try:
        proc.expect(
            r'(?i)\s*Enter\s*an\s*end\s*day:\s*'
        )
    except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        logging.error('Expected: "Enter an end day: "')
        logging.error('Could not find expected output.')
        logging.debug("%s", str(exception))
        logging.debug(str(proc))
        return status

    proc.sendline(values[i])
    i += 1
    
    try:
        proc.expect(
            r'(?i)\s*Enter\s*an\s*end\s*year:\s*'
        )
    except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        logging.error('Expected: "Enter an end year: "')
        logging.error('Could not find expected output.')
        logging.debug("%s", str(exception))
        logging.debug(str(proc))
        return status

    proc.sendline(values[i])
    i += 1
    
    try:
        proc.expect(
            r'(?i)\s*The\s+number\s+of\s+days\s+between\s+{}/{}/{}\s+and\s+{}/{}/{}\s+is\s+{}\s+days\s*'.format(*values)
        )
    except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        logging.error('Expected: "The number of days between {}/{}/{} and {}/{}/{} is {} days"'.format(*values))
        logging.error('Could not find expected output.')
        logging.debug("%s", str(exception))
        logging.debug(str(proc))
        return status
    
    proc.expect(pexpect.EOF)
    proc.close()
    if proc.exitstatus == 0:
        status = True
    return status

if __name__ == '__main__':
    cwd = os.getcwd()
    repo_name = os.path.basename(cwd)
    td = sys.argv[1]

    if sys.argv[1] == 'part-1':
        part_config = cfg.lab['parts'][0]
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
    elif sys.argv[1] == 'part-2':
        part_config = cfg.lab['parts'][1]
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
    else:
        print(f'Error: {sys.argv[0]} no match.')
        sys.exit(1)
    # Execute the solution check
    csv_solution_check_make(
        csv_key=repo_name, target_directory=td, program_name=_program_name, run=_run_func, files=_files, do_format_check=_do_format_check, do_lint_check=_do_lint_check, do_unit_tests=_do_unit_tests, tidy_options=_tidy_options, skip_compile_cmd=_skip_compile_cmd, lab_due_date=_lab_due_date
    )
