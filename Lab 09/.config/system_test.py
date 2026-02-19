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

'''
import io
import logging
import sys
import os
import re
import pexpect
import subprocess
import difflib
from assessment import csv_solution_check_simple, csv_solution_check_make
from logger import setup_logger
'''


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


_120_ERRORS = '''Introduction
tasks,
programs;
programs;
assignment;
flow;
input/output;
functions;
Structured
object-oriented
methodologies.
'''

FOX_ERRORS = ''''''

LEOTA_ERRORS = '''Serpents
spiders,
rat,
spirits,
at!
Rap
-
respond.
Send
beyond...
Goblins
ghoulies
Halloween,
tambourine!
Creepies
crawlies,
pond,
beyond!
'''

LINCOLN_ERRORS = '''Four
continent,
nation,
Liberty,
equal.
Now
war,
nation,
dedicated,
endure.
We
battle-field
war.
We
field,
live.
It
this.
'''

def run_p1(binary):
    """Run part-1"""
    logger = setup_logger()
    status = []
    error_values = (
        [None, 'error: you must give a document filename'], # 0 arguments, too few
    )
    values = (
        ['120.txt', _120_ERRORS],
        ['fox.txt', FOX_ERRORS],
        ['leota.txt', LEOTA_ERRORS],
        ['lincoln.txt', LINCOLN_ERRORS]
    )
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
            proc.expect(
                fr'(?i).*{regex}.*'
            )
        except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
            logger.error(f'Expected: "{expected}"')
            logger.error('Could not find expected output.')
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            logger.debug("%s", str(exception))
            logger.debug(str(proc))
            return status

        proc.expect(pexpect.EOF)
        proc.close()
        if proc.exitstatus == 0:
            logger.error("Expected: non-zero exit code.")
            logger.error(f'Exit code was {proc.exitstatus}.')
            logger.error("Program returned zero, but non-zero is required")
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            return status
    status = True
    return status    

def _run_p1(binary, values):
    logger = setup_logger()
    status = False
    proc = pexpect.spawn(binary, timeout=1, args=[values[0]])
    expected_errors = values[1]
    expected_output = 'spelling errors:\n' + expected_errors

    with io.BytesIO() as log_stream:
        proc.logfile = log_stream
        try:
            regex = r'(?i).*spelling\s+errors\s*:\s*\n' + expected_errors.replace('\n', '\\s+') + r'.*'
            proc.expect(regex)
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

SECRET_FILENAME = 'secret.dat'

def regex_it(s):
    combine_white_space_regex = re.compile(r"\s+")
    s = combine_white_space_regex.sub(" ", s).strip()
    s = s.replace(" ", "\\s+").replace("\n", "\\s+")
    return f"\\s*{s}\\s*"

def delete_if_exists(filename):
    try:
        os.remove(filename)
    except OSError:
        pass

def run_p2(binary):
    """Run part-2"""
    logger = setup_logger()
    status = []
    test_number = 1

    secret_errors = (
        # no arguments
        (), 

        # too many arguments
        (5, 6),

        # greater than 10
        (11,), 
        (12,),
        (100,),
        (1000,),

        # less than 1
        (0,), 
        (-1,), 
        (-100,), 
    )
    for values in secret_errors:
        logger.info("Test %d - %s", test_number, values)
        rv = _run_p2_secret_error(binary, values)
        if not rv:
            logger.error("Did not receive expected response for test %d.", test_number)
        status.append(rv)
        test_number += 1

    secret_values = list(range(1, 11))
    for value in secret_values:
        logger.info("Test %d - %s", test_number, value)
        rv = _run_p2_secret_success(binary, value)
        if not rv:
            logger.error("Did not receive expected response for test %d.", test_number)
        status.append(rv)
        test_number += 1

    game_error_values = (
        # file does not exist
        None,

        # not a number
        'snake',

        # empty
        '',

        # number out of range
        '0',
        '-1',
        '11',
        '100',
        '1000',
    )
    for value in game_error_values:
        logger.info("Test %d - %s", test_number, value)
        rv = _run_p2_game_error(binary, value)
        if not rv:
            logger.error("Did not receive expected response for test %d.", test_number)
        status.append(rv)
        test_number += 1

    game_values = (
        # win
        # omit (8, 8) because there were intermittent false-negative test failures
        (1, 1),
        (2, 2),
        (3, 3),
        (4, 4),
        (5, 5),
        (6, 6),
        (7, 7),
        (9, 9),
        (10, 10),

        # lose
        (1, 5),
        (5, 1),
        (10, 3),
        (9, 5),
        (4, 5),
    )
    for values in game_values:
        logger.info("Test %d - %s", test_number, values)
        rv = _run_p2_game_success(binary, values)
        if not rv:
            logger.error("Did not receive expected response for test %d.", test_number)
        status.append(rv)
        test_number += 1

    return status

def _run_p2_secret_error(binary, values):
    """The actual test with the expected input and output"""
    logger = setup_logger()
    status = False

    if len(values) != 1:
        argument_strings = []
        expected_output = 'error: you must provide a secret number'
    else:
        argument_strings = list(map(str, values))
        expected_output = 'error: secret number must be between 1 and 10'

    part_path = os.path.dirname(os.path.abspath(binary))
    proc = pexpect.spawn(binary, timeout=1, args=argument_strings, cwd=part_path)

    with io.BytesIO() as log_stream:
        proc.logfile = log_stream
        try:
            proc.expect(regex_it(expected_output))
        except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
            logger.error(f'Expected "{expected_output}"')
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            logger.error("Could not find expected output.")
            logger.debug("%s", str(exception))
            logger.debug(str(proc))
            return status

    proc.close()

    if proc.exitstatus == 0:
        logger.error("Expected: non-zero exit code.")
        logger.error("Program returned zero, but non-zero is required")
        return status

    status = True
    return status

def _run_p2_secret_success(binary, value):
    """The actual test with the expected input and output"""
    logger = setup_logger()
    status = False

    secret_int = value
    argument_strings = [ str(secret_int) ]

    part_path = os.path.dirname(os.path.abspath(binary))

    secret_path = os.path.join(part_path, SECRET_FILENAME)
    delete_if_exists(secret_path)

    proc = pexpect.spawn(binary, timeout=1, args=argument_strings, cwd=part_path)

    with io.BytesIO() as log_stream:
        proc.logfile = log_stream
        try:
            proc.expect(pexpect.EOF)
        except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
            logger.error(f'Expected no output')
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            logger.debug("%s", str(exception))
            logger.debug(str(proc))
            return status

    proc.close()

    if proc.exitstatus != 0:
        logger.error("Expected: zero exit code.")
        logger.error("Program returned non-zero, but zero is required")
        return status
    
    try:
        with open(os.path.join(part_path, SECRET_FILENAME)) as f:
            contents = f.read()
            if len(contents) == 0:
                logger.error(f'the "secret" program must create a file "{SECRET_FILENAME}" that contains the secret number')
                logger.error(f'"{SECRET_FILENAME}" is empty')
                return status

            if len(contents.strip()) == 0:
                logger.error(f'the "secret" program must create a file "{SECRET_FILENAME}" that contains the secret number')
                logger.error(f'"{SECRET_FILENAME}" contains only whitespace')
                return status

            try:
                got = int(contents)
            except ValueError:
                logger.error(f'the "secret" program must create a file "{SECRET_FILENAME}" that contains the secret number')
                logger.error(f'"{SECRET_FILENAME}" contains something that is not a number')
                logger.error(f'"{SECRET_FILENAME}" contents: "{contents}"')
                return status

            if got != secret_int:
                logger.error(f'the "secret" program must create a file "{SECRET_FILENAME}" that contains the secret number')
                logger.error(f'"{SECRET_FILENAME}" contains the wrong number')
                logger.error(f'the command-line argument was "{argument_strings[0]}" so "{SECRET_FILENAME}" should contain "{secret_int}"')
                logger.error(f'"{SECRET_FILENAME}" contents: "{contents}"')
                return status
    except OSError:
        logger.error(f'file "{SECRET_FILENAME}" was not created')
        logger.error(f'the "secret" program must create a file "{SECRET_FILENAME}" that contains the secret number')
        return status

    status = True
    return status

def _run_p2_game_error(binary, value):
    """The actual test with the expected input and output"""
    logger = setup_logger()
    status = False

    game_dat_contents = value

    part_path = os.path.dirname(os.path.abspath(binary))
    secret_path = os.path.join(part_path, SECRET_FILENAME)


    if game_dat_contents is None:
        # delete if it exists
        delete_if_exists(secret_path)
        expected_output = f'error: cannot read {SECRET_FILENAME}'
    else:
        with open(secret_path, 'w') as f:
            f.write(game_dat_contents)

        expected_output = f'error: {SECRET_FILENAME} malformed'

    actual_binary = os.path.join(part_path, 'game')
    proc = pexpect.spawn(actual_binary, timeout=1, args=[], cwd=part_path)

    try:
        proc.expect(regex_it(expected_output))
    except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        logger.error(f'Expected "{expected_output}"')
        logger.error("Could not find expected output.")
        logger.debug("%s", str(exception))
        logger.debug(str(proc))
        return status

    proc.close()

    if proc.exitstatus == 0:
        logger.error("Expected: non-zero exit code.")
        logger.error("Program returned zero, but non-zero is required")
        return status

    status = True
    return status

def _run_p2_game_success(binary, values):
    """The actual test with the expected input and output"""
    logger = setup_logger()
    status = False

    secret_number = values[0]
    guess = values[1]

    part_path = os.path.dirname(os.path.abspath(binary))

    with open(os.path.join(part_path, SECRET_FILENAME), 'w') as f:
        f.write(str(secret_number))

    actual_binary = os.path.join(part_path, 'game')
    proc = pexpect.spawn(actual_binary, timeout=1, args=[], cwd=part_path)

    expected_output = 'Enter your guess:'
    try:
        proc.expect(regex_it(expected_output))
    except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        logger.error(f'Expected "{expected_output}"')
        logger.error("Could not find expected output.")
        logger.debug("%s", str(exception))
        logger.debug(str(proc))
        return status

    proc.sendline(str(guess))

    if guess == secret_number:
        expected_output = 'Correct, you win!'
    else:
        expected_output = f'Incorrect, the secret number was {secret_number}, you lose.'
    try:
        proc.expect(regex_it(expected_output))
    except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        logger.error(f'Expected "{expected_output}"')
        logger.error("Could not find expected output.")
        logger.debug("%s", str(exception))
        logger.debug(str(proc))
        return status

    proc.close()

    if proc.exitstatus != 0:
        logger.error(f"Expected: zero exit code, received {proc.exitstatus} status.")
        logger.error("Program returned non-zero, but zero is required")
        return status

    status = True
    return status

if __name__ == "__main__":
    cwd = os.getcwd()
    repo_name = os.path.basename(os.path.dirname(cwd))
    td = sys.argv[1]
    # print(f'td: {td}')

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
