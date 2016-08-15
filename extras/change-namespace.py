import os
import sys
import shutil
import re
import io

project = "coconut-tools-serialisation"
src_namespace = "coconut::pulp::file_io"
dest_namespace = "coconut::pulp::serialisation"

def check_only_last_changed():
    src_head = src_namespace.split('::')[0:-1]
    dest_head = dest_namespace.split('::')[0:-1]
    if src_head != dest_head:
        raise RuntimeError('Only the last part of the namespace is allowed to change')

def namespace_to_dir(namespace):
    return "/".join(namespace.split('::')).replace('_', '-')

def namespace_to_include_guard(namespace):
    return namespace.replace('::', '_').upper()

def refactor_include_guard(line):
    include_guard_src = namespace_to_include_guard(src_namespace)
    include_guard_line_re = re.compile('^(#((ifndef)|(define)|(endif)).*)%s(.*)$' % include_guard_src)
    match = include_guard_line_re.match(line)
    if match:
        include_guard_dest = namespace_to_include_guard(dest_namespace)
        new_line = match.group(1) + include_guard_dest + match.group(6)
        sys.stderr.write('* %s -> %s\n' % (line, new_line))
        line = new_line
    return line

def refactor_namespace_declaration(line):
    namespace_declaration_re = re.compile('(namespace\s+)%s([^\w]|$)' % src_namespace.split('::')[-1])
    new_line = namespace_declaration_re.sub(r'\1%s\2' % dest_namespace.split('::')[-1], line)
    if new_line != line:
        sys.stderr.write('* %s -> %s\n' % (line, new_line))
        line = new_line
    return line

def refactor_using_namespace(line):
    namespace_declaration_re = re.compile('(using\s+namespace\s+)%s([^\w]|$)' % src_namespace)
    new_line = namespace_declaration_re.sub(r'\1%s\2' % dest_namespace, line)
    if new_line != line:
        sys.stderr.write('* %s -> %s\n' % (line, new_line))
        line = new_line
    return line

def refactor_namespace_specifier(line):
    namespace_declaration_re = re.compile('%s::' % src_namespace.split('::')[-1])
    new_line = namespace_declaration_re.sub('%s::' % dest_namespace.split('::')[-1], line)
    if new_line != line:
        sys.stderr.write('* %s -> %s\n' % (line, new_line))
        line = new_line
    return line

def get_line_feed(line):
    line_feed_re = re.compile('^([^\r\n]*)(\r?\n?)$')
    match = line_feed_re.match(line)
    if not match:
        raise RuntimeError('Unexpected line: ' + line)
    return match.group(1), match.group(2)

def refactor_header(f):
    sys.stderr.write('*** refactoring %s\n' % f)
    working_f = f + '.refactored'
    with io.open(f, newline='') as in_f, io.open(working_f, 'w', newline='') as out_f:
        for line in in_f.readlines():
            content, line_feed = get_line_feed(line)
            content = refactor_include_guard(content)
            content = refactor_namespace_declaration(content)
            content = refactor_using_namespace(content)
            content = refactor_namespace_specifier(content)
            out_f.write(content + line_feed)
    shutil.move(working_f, f)

def refactor_impl(f):
    sys.stderr.write('*** refactoring %s\n' % f)
    working_f = f + '.refactored'
    with io.open(f, newline='') as in_f, io.open(working_f, 'w', newline='') as out_f:
        for line in in_f.readlines():
            content, line_feed = get_line_feed(line)
            content = refactor_using_namespace(content)
            content = refactor_namespace_specifier(content)
            out_f.write(content + line_feed)
    shutil.move(working_f, f)

check_only_last_changed()

for type_dir in [ 'main', 'test', 'functional-test' ]:
    root_src_dir = "%(project)s/src/%(type_dir)s/c++/" % locals() + namespace_to_dir(src_namespace)
    root_dest_dir = "%(project)s/src/%(type_dir)s/c++/" % locals() + namespace_to_dir(dest_namespace)

    if os.path.isdir(root_src_dir):
        shutil.move(root_src_dir, root_dest_dir)

        for root, dirs, files in os.walk(root_dest_dir):
            for f in files:
                if f.endswith('.h') or f.endswith('.hpp'):
                    refactor_header('%s/%s' % (root, f))
                elif f.endswith('.cpp') or f.endswith('.cxx'):
                    refactor_impl('%s/%s' % (root, f))
