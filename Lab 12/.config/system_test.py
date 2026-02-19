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
import shutil
import subprocess
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


def _run_p1_error(binary, values):
    logger = setup_logger()
    status = False
    if values[0] == "Empty":
        proc = pexpect.spawn(binary, timeout=1)
    else:
        proc = pexpect.spawn(binary, timeout=1, args=values[:2])
    # proc.logfile = sys.stdout.buffer
    # values = list(map(str, values))

    with io.BytesIO() as log_stream:
        proc.logfile = log_stream
        try:
            regex = values[-1].replace(' ', '\\s+')
            proc.expect(
                fr'(?i).*{regex}.*'
            )
        except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
            expected_output = values[-1]
            logger.error(f'Expected: "{expected_output}"')
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


def run_p1(binary):
    """Run part-1"""
    logger = setup_logger()
    status = []
    error_values = (
        ['Empty', 'Please provide a path to a file'], # 0 arguments, too few
        ['/foobar', '/foobar is missing the required file extension .gif.'], # Missing image format
    )
    values = (
                ['test_output.gif', 'sample_images/sample_image.gif'],
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


def _run_p1(binary, values):
    """The actual test with the expected input and output"""
    logger = setup_logger()
    status = True
    proc = pexpect.spawn(binary, timeout=60, args=[values[0]])
    # proc.logfile = sys.stdout.buffer
    # values = list(map(str, values))

    with io.BytesIO() as log_stream:
        proc.logfile = log_stream
        # try:
        #     proc.expect(
        #         fr'(?i).*'
        #     )
        # except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        #     # logger.error(f'Expected: "{expected_output}"')
        #     logger.error('Could not find expected output.')
        #     logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
        #     logger.debug("%s", str(exception))
        #     logger.debug(str(proc))
        #     status = False
        #     return status       

        proc.expect(pexpect.EOF)
                
        proc.close()
        
        if proc.exitstatus != 0:
            logger.error("Expected: zero exit code.")
            logger.error(f'Exit code was {proc.exitstatus}.')
            logger.error("Program returned non-zero, but zero is required")
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            status = False

    if status and shutil.which('gm'):
        if os.path.exists(values[0]) and os.path.exists(values[1]):
            gm_cmd = shutil.which('gm') + ' compare -metric PAE -highlight-style XOR -highlight-color purple -file diff.png {} {}'.format(*values)
            logger.debug(f'Executing {gm_cmd}')
            proc = subprocess.run(
                [gm_cmd],
                capture_output=True,
                shell=True,
                timeout=4,
                check=False,
                text=True,
            )
            regex = r'(?i)(Red|Green|Blue|Total):\s+(\d+\.\d+)\s+(\d+\.\d+)'
            peak_error = {}
            for line in str(proc.stdout).split('\n'):
                match = re.search(regex, line)
                if match:
                    key = match.group(1).lower()
                    peak_error[key] = (float(match.group(2)), float(match.group(3)))
            logger.info('Analyzed difference between "{}" and "{}"'.format(*values))
            if 'total' in peak_error:
                total_error = peak_error['total'][0]
                max_error = 0.0015
                if total_error > max_error:
                    logger.error('❌ Output image has too much error.')
                    status = False
                for key in peak_error.keys():
                    percentage = '{:0.2f}'.format(peak_error[key][0] * 100.0)
                    prefix = '✅ '
                    if peak_error[key][0] > max_error:
                        prefix = '❌ '
                    logger.info(f'{prefix}{key.title()}: {percentage}% error')
            else:
                logger.error('❌ Missing total error measure in analysis.')
                status = False
        else:
            logger.error('❌ Missing output or sample output.')
            status = False

    elif status:
        logger.error('❌ Missing GraphicsMagick; cannot verify output.')
        logger.error('Please install base packages using the command:')
        logger.error('wget -q https://raw.githubusercontent.com/mshafae/tusk/main/quickinstall.sh -O- | sh')
        status = False
    return status


def run_p2(binary):
    """Run part-2"""
    logger = setup_logger()
    status = []
    error_values = (
        ['Empty', 'Please provide a path to a file'], # 0 arguments, too few
        ['/foobar', '/foobar is missing the required file extension .gif.'], # Missing image format
    )
    values = (
                ['test_output.gif', 'CPSC 120A', 'sample_images/sample_image.gif'],
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
        rv = _run_p2(binary, val)
        if not rv:
            logger.error("Did not receive expected response for test %d.", test_number)
        status.append(rv)
    return status

def _run_p2(binary, values):
    """The actual test with the expected input and output"""
    logger = setup_logger()
    status = True
    proc = pexpect.spawn(binary, timeout=60, args=values[:2])
    # proc.logfile = sys.stdout.buffer
    # values = list(map(str, values))

    with io.BytesIO() as log_stream:
        proc.logfile = log_stream
        # try:
        #     proc.expect(
        #         fr'(?i).*'
        #     )
        # except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
        #     # logger.error(f'Expected: "{expected_output}"')
        #     logger.error('Could not find expected output.')
        #     logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
        #     logger.debug("%s", str(exception))
        #     logger.debug(str(proc))
        #     status = False
        #     return status       

        proc.expect(pexpect.EOF)
                
        proc.close()
        
        if proc.exitstatus != 0:
            logger.error("Expected: zero exit code.")
            logger.error(f'Exit code was {proc.exitstatus}.')
            logger.error("Program returned non-zero, but zero is required")
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            status = False

    img_filenames = [values[0], values[2]]
    if status and shutil.which('gm'):
        if os.path.exists(values[0]) and os.path.exists(values[2]):
            gm_cmd = shutil.which('gm') + ' compare -metric PAE -highlight-style XOR -highlight-color purple -file diff.png {} {}'.format(*img_filenames)
            logger.debug(f'Executing {gm_cmd}')
            proc = subprocess.run(
                [gm_cmd],
                capture_output=True,
                shell=True,
                timeout=4,
                check=False,
                text=True,
            )
            regex = r'(?i)(Red|Green|Blue|Total):\s+(\d+\.\d+)\s+(\d+\.\d+)'
            peak_error = {}
            for line in str(proc.stdout).split('\n'):
                match = re.search(regex, line)
                if match:
                    key = match.group(1).lower()
                    peak_error[key] = (float(match.group(2)), float(match.group(3)))
            logger.info('Analyzed difference between "{}" and "{}"'.format(*img_filenames))
            if 'total' in peak_error:
                total_error = peak_error['total'][0]
                max_error = 0.0015
                if total_error > max_error:
                    logger.error('❌ Output image has too much error.')
                    status = False
                for key in peak_error.keys():
                    percentage = '{:0.2f}'.format(peak_error[key][0] * 100.0)
                    prefix = '✅ '
                    if peak_error[key][0] > max_error:
                        prefix = '❌ '
                    logger.info(f'{prefix}{key.title()}: {percentage}% error')
            else:
                logger.error('❌ Missing total error measure in analysis.')
                status = False
        else:
            logger.error('❌ Missing output or sample output.')
            status = False

    elif status:
        logger.error('❌ Missing GraphicsMagick; cannot verify output.')
        logger.error('Please install base packages using the command:')
        logger.error('wget -q https://raw.githubusercontent.com/mshafae/tusk/main/quickinstall.sh -O- | sh')
        status = False
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
