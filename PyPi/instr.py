# # Update tools
# python -m pip install --user --upgrade setuptools wheel
#
# # Create dist pckg
# python setup.py sdist bdist_wheel
#
# # Install twine
# python -m pip install --user --upgrade twine
#
# # Upload to TestPyPi
# python -m twine upload --repository-url https://test.pypi.org/legacy/ dist/*
#
# # Upload to PyPi
# python -m twine upload dist/*
import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name="package_name",
    version="1.0.0",
    author="author",
    author_email="email@email.com",
    description="A short description",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/author_name/project_name",
    packages=setuptools.find_packages(),
    classifiers=[
        # https://pypi.org/classifiers/
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
)
