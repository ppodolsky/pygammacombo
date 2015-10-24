import platform
import os, errno
import subprocess
import tempfile
import shutil
import re

from .meta import *

rename = os.rename
move = os.rename


def include_paths(name):
    database = {'python': ('python', 'includes', r"-I(.*?)(?=\s-I|$)"),
                'python3': ('python3', 'includes', r"-I(.*?)(?=\s-I|$)"),
                'root': ('root', 'incdir', None)}
    if name in database.keys():
        config = database[name]
        return get_config(*config)
    else:
        raise ValueError("{}-config is not supported by megazord. Invoke neccesary information manually.".format(name))


def library_paths(name):
    database = {'python': ('python', 'ldflags', r"-L(.*?)(?=\s-l|$)"),
                'python3': ('python3', 'ldflags', r"-L(.*?)(?=\s-l|$)"),
                'root': ('root', 'libdir', None)}
    if name in database.keys():
        config = database[name]
        return get_config(*config)
    else:
        raise ValueError("{}-config is not supported by megazord. Invoke neccesary information manually.".format(name))


def library(name):
    database = {'python': ('python', 'libs', r"-l(.*?)(?=\s-|$)"),
                'python3': ('python3', 'libs', r"-l(.*?)(?=\s-|$)"),
                'root': ('root', 'libs', r"-l(.*?)(?=\s-|$)")}
    if name in database.keys():
        config = database[name]
        return get_config(*config)
    else:
        raise ValueError("{}-config is not supported by megazord. Invoke neccesary information manually.".format(name))


def get_config(name, arg, r=None):
    result = subprocess.check_output(["{}-config".format(name), "--{}".format(arg)])[:-1].decode("utf-8")
    if r is not None:
        result = re.findall(r, result)
    else:
        result = [result]
    return result


def call(cmd, args):
    t = [cmd]
    t.extend(args)
    print("Run: {}".format(' '.join(t)))
    return subprocess.check_output(t)


def locate_file(name):
    result = subprocess.check_output(["which", name])[:-1].decode("utf-8")
    if result is None:
        os_name = platform.system()
        if os_name in megazord.meta.search_paths.keys():
            result = search(name, megazord.meta.search_paths[os_name])
    return result


def mkdir_p(path):
    try:
        os.makedirs(path)
    except OSError as exc:  # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else:
            raise


def rm(path):
    info('removing {} ...'.format(path), 2)
    if os.path.isdir(path):
        shutil.rmtree(path)
    else:
        os.remove(path)


getwd = os.getcwd
setwd = os.chdir


def which(name):
    return subprocess.check_output(["which", name])[:-1].decode("utf-8")


def search(name, paths):
    for path in paths:
        compiler_path = path + name
        if os.path.isfile(compiler_path):
            return compiler_path
    return None


def mkdtemp(dir="."):
    r = tempfile.mkdtemp(dir=dir)
    info('creation temp directory {} ...'.format(r), 2)
    return r



def warning(text, *args):
    print("Warning: {}".format(text.format(args)))


def info(text, verbose=1, *args):
    if megazord.verbose >= verbose:
        print("Info: {}".format(text.format(args)))
