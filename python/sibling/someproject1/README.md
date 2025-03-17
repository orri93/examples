# Sibling package import example

## Tired of sys.path hacks?

There are plenty of `sys.path.append` -hacks available, but I found an alternative way of solving the problem in hand.

### Summary

* Wrap the code into one folder (e.g. `packaged_stuff`)
* Create `pyproject.toml` file to describe your package (see minimal `pyproject.toml` below)
* Pip install the package in editable state with `pip install -e <myproject_folder>`
* Import using `from packaged_stuff.modulename import function_name`

## Setup

The starting point is the file structure you have provided, wrapped in a folder called `myproject`.

```
.
└── myproject
    ├── api
    │   ├── api_key.py
    │   ├── api.py
    │   └── __init__.py
    ├── examples
    │   ├── example_one.py
    │   ├── example_two.py
    │   └── __init__.py
    ├── LICENCE.md
    ├── README.md
    └── tests
        ├── __init__.py
        └── test_one.py
```

I will call the `.` the root folder, and in my example case it is located at `C:\tmp\test_imports\.`

### api.py

As a test case, let's use the following ./api/api.py

```python
def function_from_api():
  return 'I am the return value from api.api!'
```

### test_one.py

```python
from api.api import function_from_api

def test_function():
  print(function_from_api())

if __name__ == '__main__':
  test_function()
```

### Try to run test_one:

```ps
PS C:\tmp\test_imports> python .\myproject\tests\test_one.py
Traceback (most recent call last):
  File ".\myproject\tests\test_one.py", line 1, in <module>
    from api.api import function_from_api
ModuleNotFoundError: No module named 'api'
```

### Also trying relative imports wont work:

Using `from ..api.api import function_from_api` would result into

```ps
PS C:\tmp\test_imports> python .\myproject\tests\test_one.py
Traceback (most recent call last):
  File ".\tests\test_one.py", line 1, in <module>
    from ..api.api import function_from_api
ValueError: attempted relative import beyond top-level package
```

# Steps

**1) Make a pyproject.toml file to the root level directory**

(previously people used a setup.py file)

The contents for a minimal `pyproject.toml` would be*

```
[project]
name = "myproject"
version = "0.1.0"
description = "My small project"

[build-system]
build-backend = "flit_core.buildapi"
requires = ["flit_core >=3.2,<4"]
```

**2) Use a virtual environment**

*If you are familiar with virtual environments, activate one, and skip to the next step.* Usage of virtual environments are not absolutely required, but they will really help you out in the long run (when you have more than 1 project ongoing..). The most basic steps are (run in the root folder)

* Create virtual env

  * `python -m venv venv`

* Activate virtual env
  * `source ./venv/bin/activate` (Linux, macOS) or `./venv/Scripts/activate` (Win)

To learn more about this, just Google out "python virtual env tutorial" or similar. You probably never need any other commands than creating, activating and deactivating.

Once you have made and activated a virtual environment, your console should give the name of the virtual environment in parenthesis

```
PS C:\tmp\test_imports> python -m venv venv
PS C:\tmp\test_imports> .\venv\Scripts\activate
(venv) PS C:\tmp\test_imports>
```

and your folder tree should look like this**

```
.
├── myproject
│   ├── api
│   │   ├── api_key.py
│   │   ├── api.py
│   │   └── __init__.py
│   ├── examples
│   │   ├── example_one.py
│   │   ├── example_two.py
│   │   └── __init__.py
│   ├── LICENCE.md
│   ├── README.md
│   └── tests
│       ├── __init__.py
│       └── test_one.py
├── pyproject.toml
└── venv
    ├── Include
    ├── Lib
    ├── pyvenv.cfg
    └── Scripts [87 entries exceeds filelimit, not opening dir]
```

**3) pip install your project in editable state**

Install your top level package `myproject` using pip. The trick is to use the `-e` flag when doing the install. This way it is installed in an editable state, and all the edits made to the .py files will be automatically included in the installed package. *Using pyproject.toml and -e flag requires pip >= 21.3*

In the root directory, run

`pip install -e .` (note the dot, it stands for "current directory")

You can also see that it is installed by using pip freeze

```
Obtaining file:///home/user/projects/myproject
  Installing build dependencies ... done
  Checking if build backend supports build_editable ... done
  Getting requirements to build editable ... done
  Preparing editable metadata (pyproject.toml) ... done
Building wheels for collected packages: myproj
  Building editable for myproj (pyproject.toml) ... done
  Created wheel for myproj: filename=myproj-0.1.0-py2.py3-none-any.whl size=903 sha256=f19858b080d4e770c2a172b9a73afcad5f33f4c43c86e8eb9bdacbe50a627064
  Stored in directory: /tmp/pip-ephem-wheel-cache-qohzx1u0/wheels/55/5f/e4/507fdeb40cdef333e3e0a8c50c740a430b8ce84cbe17ae5875
Successfully built myproject
Installing collected packages: myproject
Successfully installed myproject-0.1.0
(venv) PS C:\tmp\test_imports> pip freeze
myproject==0.1.0
```

**4) Add myproject. into your imports**

Note that you will have to add `myproject`. only into imports that would not work otherwise. Imports that worked without the `pyproject.toml` & `pip install` will work still work fine. See an example below.

# Test the solution

Now, let's test the solution using `api.py` defined above, and `test_one.py` defined below.

## test_one.py

```python
from myproject.api.api import function_from_api

def test_function():
  print(function_from_api())

if __name__ == '__main__':
  test_function()
```

## running the test

```
(venv) PS C:\tmp\test_imports> python .\myproject\tests\test_one.py
I am the return value from api.api!
```

# Notes

\* here using flit as build backend. Other alternatives exist.

\** In reality, you could put your virtual environment anywhere on your hard disk.

# Reference
* [Sibling package imports](https://stackoverflow.com/questions/6323860/sibling-package-imports)