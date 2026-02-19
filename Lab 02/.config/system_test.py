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

def liberal_regex_it(s):
    s = s.replace('.', ' ').replace(',', ' ')
    combine_white_space_regex = re.compile(r"\s+")
    s = combine_white_space_regex.sub(" ", s).strip()
    s = s.replace(' ', '\\W+').replace('\n', '\\W+')
    return f'\\s*{s}\\s*'

def run_p1(binary):
    """Run part-1"""
    logger = setup_logger()
    status = []
    error_values = ()
    values = (
        tuple('cat dogs live'.split()),
        tuple('car helicopters spin'.split()),
        tuple('fork knives flip'.split()),
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
    raise NotImplementedError

def _run_p1(binary, values):
    """The actual test with the expected input and output"""
    logger = setup_logger()
    status = False
    proc = pexpect.spawn(binary, timeout=1)
    # proc.logfile = sys.stdout.buffer
    # values = list(map(str, values))
    prompts = (
        "Please enter a singular noun:",
        "Please enter a plural noun:",
        "Please enter a present tense verb:",
    )
    expected_output = f'Computers are small enough to fit into a {values[0]}.\nComputers can add, multiply, divide, and {values[2]}.\nPeople can {values[2]} too but computers do it better.\nComputers have many {values[1]} which gives them the advantage\nover people for many computational tasks.\n'
    
    #expected_regex = expected_output.replace(' ', '\\s+').replace('\n', '\\s+').replace(',', '[,?]')
    values_iter = iter(values)
    with io.BytesIO() as log_stream:
        proc.logfile = log_stream
        
        for p,v in zip(prompts, values):
            p_regex = regex_it(p)
            try:
                proc.expect(
                    fr'(?i){p_regex}'
                )
            except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
                logger.error('Could not find expected output.')
                logger.error(f'Expected "{p}"')
                logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
                logger.debug("%s", str(exception))
                logger.debug(str(proc))
                return status
        
            proc.sendline(v)
        
        
        try:
            expected_output_regex = liberal_regex_it(expected_output)
            #print(expected_output_regex)
            #print(expected_output)
            proc.expect(
                fr'(?i){expected_output_regex}'
            )
        except (pexpect.exceptions.TIMEOUT, pexpect.exceptions.EOF) as exception:
            logger.error('Could not find expected output.')
            logger.error(f'Expected\n"{expected_output}"')
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
            logger.debug("%s", str(exception))
            logger.debug(str(proc))
            return status

        proc.expect(pexpect.EOF)
        proc.close()
        if proc.exitstatus == 0:
            status = True
        else:
            logger.error("Expected: zero exit code.")
            logger.error(f'Exit code was {proc.exitstatus}.')
            logger.error("Program returned non-zero, but zero is required")
            logger.error('Your output: "%s"', log_stream.getvalue().decode('utf-8'))
    
    return status

# Tidy options used on this lab in Spring 2023. Move these to lab_config.py if necessary.
'''
tidy_opts = (
    '-checks="*,-misc-unused-parameters,'
    '-modernize-use-trailing-return-type,-google-build-using-namespace,'
    '-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,'
    '-fuchsia-default-arguments-calls,-clang-analyzer-deadcode.DeadStores,'
    '-modernize-use-nodiscard,-modernize-pass-by-value,'
    '-bugprone-exception-escape,-llvm-header-guard"'
    ' -config="{CheckOptions: [{key: readability-identifier-naming.ClassCase, value: CamelCase}, '
    '{key: readability-identifier-naming.ClassMemberCase, value: lower_case}, '
    '{key: readability-identifier-naming.ConstexprVariableCase, value: CamelCase}, '
    '{key: readability-identifier-naming.ConstexprVariablePrefix, value: k}, '
    '{key: readability-identifier-naming.EnumCase, value: CamelCase}, '
    '{key: readability-identifier-naming.EnumConstantCase, value: CamelCase}, '
    '{key: readability-identifier-naming.EnumConstantPrefix, value: k}, '
    '{key: readability-identifier-naming.FunctionCase, value: CamelCase}, '
    '{key: readability-identifier-naming.GlobalConstantCase, value: CamelCase}, '
    '{key: readability-identifier-naming.GlobalConstantPrefix, value: k}, '
    '{key: readability-identifier-naming.StaticConstantCase, value: CamelCase}, '
    '{key: readability-identifier-naming.StaticConstantPrefix, value: k}, '
    '{key: readability-identifier-naming.StaticVariableCase, value: lower_case}, '
    '{key: readability-identifier-naming.MacroDefinitionCase, value: UPPER_CASE}, '
    '{key: readability-identifier-naming.MacroDefinitionIgnoredRegexp, value: \'^[A-Z]+(_[A-Z]+)*_$\'}, '
    '{key: readability-identifier-naming.MemberCase, value: lower_case}, '
    '{key: readability-identifier-naming.PrivateMemberSuffix, value: _}, '
    '{key: readability-identifier-naming.PublicMemberSuffix, value: \'\'}, '
    '{key: readability-identifier-naming.NamespaceCase, value: lower_case}, '
    '{key: readability-identifier-naming.ParameterCase, value: lower_case}, '
    '{key: readability-identifier-naming.TypeAliasCase, value: CamelCase}, '
    '{key: readability-identifier-naming.TypedefCase, value: CamelCase}, '
    '{key: readability-identifier-naming.VariableCase, value: lower_case}, '
    '{key: readability-identifier-naming.IgnoreMainLikeFunctions, value: 1}]}"'
)
'''

tidy_opts = cfg.global_tidy_options_string

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

