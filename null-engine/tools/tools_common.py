import argparse
import enum
import subprocess
import sys
import warnings


class DevPlatform(enum.Enum):
    """Plaform support for project development"""
    LINUX   = 0
    WINDOWS = 1

    @classmethod
    def from_string(cls, string):
        string = string.lower()
        if string == "linux":
            return cls.LINUX
        elif string == "windows":
            return cls.WINDOWS


class BuildPlatform(enum.Enum):
    """Platform support for final product"""
    LINUX   = 0
    WINDOWS = 1

    @classmethod
    def from_string(cls, string):
        string = string.lower()
        if string == "linux":
            return cls.LINUX
        elif string == "windows":
            return cls.WINDOWS


_log_state = {
    "trace": False,
    "info" : False,
    "debug": False,
    "warn" : False,
    "error": False,
    "fatal": False,
}

_current_devplatform = None
_current_buildplatform = None


def platform_register_cmd_args(parser):
    parser.add_argument("--dev-platform",   choices=["linux", "windows"], required=True, help="Platform the project is being built on")
    parser.add_argument("--build-platform", choices=["linux", "windows"], required=True, help="Platform the project is being built for")


def platform_parse_cmd_args(parser, args):
    global _current_devplatform, _current_buildplatform
    _current_devplatform   = DevPlatform.from_string(args.dev_platform)
    _current_buildplatform = BuildPlatform.from_string(args.build_platform)


def get_devplatform():
    return _current_devplatform


def get_buildplatform():
    return _current_buildplatform


def logger_register_cmd_args(parser):
    parser.add_argument("-v", "--verbose", action="count", default=0, help="Increase verbosity (default=warn, -v=info, -vv=trace)")
    parser.add_argument("-q", "--quiet",   action="count", default=0, help="Decrease verbosity (default=warn, -q=error, -qq=fatal)")


def logger_parse_cmd_args(parser, args):
    global _log_state
    log_level = args.verbose - args.quiet
    _log_state["fatal"] = True
    if log_level >= -1:
        _log_state["error"] = True
    if log_level >= 0:
        _log_state["warn"] = True
    if log_level >= 1:
        _log_state["info"] = True
    if log_level >= 2:
        _log_state["trace"] = True


def logger_use_vapi():
    """:returns true if one should enable verbose flags in API calls"""
    return _log_state["trace"]


def logger_trace(*args):
    if _log_state["trace"]:
        print("[TRACE]", *args, flush=True, file=sys.stdout)


def logger_info(*args):
    if _log_state["info"]:
        print("[INFO] ", *args, flush=True, file=sys.stdout)


def logger_debug(*args):
    if _log_state["debug"]:
        print("[DEBUG]", *args, flush=True, file=sys.stdout)


def logger_warn(*args):
    if _log_state["warn"]:
        print("[WARN] ", *args, flush=True, file=sys.stderr)


def logger_error(*args):
    if _log_state["error"]:
        print("[ERROR]", *args, flush=True, file=sys.stderr)


def logger_fatal(*args):
    if _log_state["fatal"]:
        print("[FATAL]", *args, file=sys.stderr)
        sys.exit(-1)


def run_process(executable, *args):
    logger_info(f"Running executable: [{executable}]")
    logger_trace(f"Arguments provided: [{args}]")
    result = subprocess.run([executable, *args], capture_output=True, text=True)
    if result.returncode == 0:
        logger_info(f"Executable finished successfully")
    else:
        logger_fatal(f"Executable finished with non-zero exit code [{result.returncode}]\nProcess stdout:\n{result.stdout}\nProcess stderr:\n{result.stderr}")
    logger_trace(f"Process stdout: {result.stdout}")
    return result
