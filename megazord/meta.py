import megazord

search_paths = {'Darwin':
                    ['/usr/bin/', '/usr/local/bin/'],
                'Linux':
                    ['/usr/bin/', '/usr/local/bin/']}


def get_compiler_by_language(language):
    compiler_by_language = {'c': ['clang', 'gcc'],
                            'c++': ['clang++', 'g++'],
                            'd': ['dmd'],
                            'object': ['clang++', 'g++', 'clang', 'gcc'],
                            'java': ['javac'],
                            'javacode': ['jar']}
    if language in compiler_by_language:
        for compiler_name in compiler_by_language[language]:
            compiler = get_compiler_by_name(compiler_name)
            if compiler is not None:
                return compiler
    return None


def get_compiler_by_name(name):
    compilers_by_name = {'clang': megazord.ClangCompiler,
                         'clang++': megazord.ClangppCompiler,
                         'gcc': megazord.GccCompiler,
                         'g++': megazord.GppCompiler,
                         'dmd': megazord.DmdCompiler,
                         'javac': megazord.JavaCompiler,
                         'jar': megazord.JarCompiler}
    path = megazord.system.locate_file(name)
    if name in compilers_by_name.keys() and path is not None:
        return compilers_by_name[name](path=path)
    return None


def get_default_output_format_for_language(language):
    default_formats = {
        'c++': '.a',
        'c': '.a',
        'd': '.a',
        'java': '.class',
        'javacode': '.jar',
        'object': '.a'
    }
    if language in default_formats:
        return default_formats[language]
    return ''


def get_language_by(extensions):
    languages_by_extension = {'.c': 'c',
                              '.cpp': 'c++',
                              '.java': 'java',
                              '.class': 'javacode',
                              '.d': 'd',
                              '.o': 'object'}
    used_languages = set(
        map(lambda x: languages_by_extension[x] if x in languages_by_extension else 'unknown', extensions))
    if 'c' in used_languages and 'c++' in used_languages:
        used_languages.remove('c')
    return list(used_languages)


def get_default_libraries(format):
    default_libraries = {
    }
    if format in default_libraries:
        return default_libraries[format]
    return []


def get_default_includies(format):
    default_includies = {
        'clang++': ['/usr/local/include'],
        'clang': ['/usr/local/include'],
        'g++': ['/usr/local/include'],
        'gcc': ['/usr/local/include'],
    }
    if format in default_includies:
        return default_includies[format]
    return []
