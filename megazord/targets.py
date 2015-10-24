import re
import os
import glob
import megazord


class Target:
    def __init__(self, sources, output=None, compiler=None, entry_point=None, delayed=True):
        # Parse sources
        self.delayed = delayed
        self.sources_arg = sources
        self.output_arg = output
        self.compiler_arg = compiler
        self.sources_names = None
        self.sources_formats = None
        self.language = 'unknown'

        if not self.delayed:
            self.set_sources(self.sources_arg)
            self.__detect_language()
            self.set_output(self.output_arg)
            self.set_compiler(self.compiler_arg)

        self.set_entry_point(entry_point)
        self.optimization_level = 0
        self.libraries = []
        self.includies = []
        self.library_paths = []
        self.include_paths = []
        self.dependencies = []

    def set_optimization_level(self, optimization_level):
        self.optimization_level = optimization_level
        return self

    def get_sources(self):
        return self.sources

    def depends_on(self, *args):
        self.dependencies.extend(args)
        return self

    def add_library(self, name):
        if isinstance(name, list):
            self.libraries.extend(name)
        else:
            self.libraries.append(name)
        return self

    def add_library_path(self, path):
        if isinstance(path, list):
            self.library_paths.extend(path)
        else:
            self.library_paths.append(path)
        return self

    def add_include(self, name):
        if isinstance(name, list):
            self.includies.extend(name)
        else:
            self.includies.append(name)
        return self

    def add_include_path(self, path):
        if isinstance(path, list):
            self.include_paths.extend(path)
        else:
            self.include_paths.append(path)
        return self

    def __detect_language(self):
        self.language = megazord.meta.get_language_by(self.sources_formats)
        if len(self.language) > 1:
            raise ValueError("Multiple languages detected in {}".format(self.sources))
        else:
            self.language = self.language[0]

    def set_output(self, output):
        self.output = output
        if self.output is None:
            self.output = self.sources_names[0] + megazord.meta.get_default_output_format_for_language(self.language)
            self.output_dir = ''
        elif self.output.endswith('/'):
            self.output_dir = self.output
            self.output = self.sources_names[0] + megazord.meta.get_default_output_format_for_language(self.language)
        else:
            self.output_dir = os.path.dirname(os.path.relpath(self.output))
            self.output = os.path.basename(self.output)

        if len(self.output_dir) == 0:
            self.output_dir = '.'
        if not self.output_dir.endswith('/'):
            self.output_dir += '/'

        megazord.system.mkdir_p(self.output_dir)
        self.output_name, self.output_format = os.path.splitext(self.output)
        return self

    def set_entry_point(self, entry_point):
        self.entry_point = entry_point
        return self

    def set_output_name(self, name):
        self.output_name = name
        return self

    def set_output_dir(self, dir):
        self.output_dir = dir
        megazord.system.mkdir_p(dir)
        return self

    def set_compiler(self, compiler):
        self.compiler = compiler
        if isinstance(self.compiler, megazord.GenericCompiler):
            pass
        elif isinstance(self.compiler, str):
            self.compiler = megazord.meta.get_compiler_by_name(self.compiler)
            if self.compiler is None:
                raise FileNotFoundError("{} was not found.".format(compiler))
        elif self.compiler is None:
            self.compiler = megazord.meta.get_compiler_by_language(self.language)
            if self.compiler is None:
                raise FileNotFoundError("No compiler for {} was found.".format(self.language))
        megazord.system.info("{} used for the target {}".format(self.compiler.name, self.sources))
        return self

    def set_sources(self, sources):
        self.sources = []
        if isinstance(sources, str):
            sources = [sources]
        for files in sources:
            self.sources.extend(glob.glob(files))
        self.sources_names, self.sources_formats = list(map(list, zip(*[os.path.splitext(s) for s in self.sources])))
        return self

    def assembly(self):
        for dependency in self.dependencies:
            dependency.assembly()
        if self.delayed:
            self.set_sources(self.sources_arg)
            self.__detect_language()
            self.set_output(self.output_arg)
            self.set_compiler(self.compiler_arg)
        self.compiler.compile(self)
        return self
