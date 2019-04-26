from cx_Freeze import Executable
from cx_Freeze import setup

# Dependencies are automatically detected, but it might need
# fine tuning.
buildOptions = dict(
    packages=[],
    excludes=[],
    includes=[
        "idna.idnadata"  # for requests module
        ]
)

base = 'Console'  # "Win32GUI"

executables = [
    Executable(
        '<path_to_py_script>',
        base=base,
        targetName='<exec_name>'
    )
]

setup(
    name='<project_name>',
    version='1.0',
    description='desc',
    options=dict(build_exe=buildOptions),
    executables=executables
)
