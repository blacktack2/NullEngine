import argparse
import datetime
import re
import os

from tools_common import *


def create_shader_list(outfile, shaders, macro):
    if os.path.isfile(outfile):
        with open(outfile, "r") as f:
            existing = f.read()
    else:
        existing = ""

    lines = existing.split("\n")
    default_lines = [
        "#pragma once",
        "//",
        "",
        "#include \"NE/Math/MathTypes.h\"",
        "",
        "typedef null::math::size shader_id;"
        "",
    ]
    if any([(i >= len(lines) or (i != 1 and l != lines[i])) for i, l in enumerate(default_lines)]):
        logger_warn("Invalid shader-list file. Overwriting contents")
        lines = default_lines + [""]

    with open(outfile, "w") as f:
        lines[1] = f"// Auto-generated file (DO NOT EDIT) created on '{datetime.datetime.now()}'"

        macro_begin_match = [(s, i) for i, s in enumerate(lines) if f"#if {macro}" in s]
        macro_end_match   = [(s, i) for i, s in enumerate(lines) if f"#endif" in s]

        for _, start_idx in macro_begin_match:
            end_idx = len(lines) - 1
            for _, end in macro_end_match:
                if end > start_idx:
                    end_idx = end
                    break
            logger_info(f"List found for macro '{macro}' between lines {start_idx} and {end_idx}")
            lines = lines[:start_idx - 1] + lines[end_idx + 1:]

        shadernames = []
        for shaderabs, shaderrel in shaders:
            shadernames.append(re.sub("[\\/\-.]", "_", os.path.splitext(shaderrel)[0]))

        lines.append(f"#if {macro}")
        lines.append("")
        lines.append("enum class ShaderId : shader_id")
        lines.append("{")
        lines.append("\n".join([f"    {name}," for name in shadernames]))
        lines.append("    _Max,")
        lines.append("};")
        lines.append("")
        lines.append("const char* g_shaderSources[(null::math::size)ShaderId::_Max] =")
        lines.append("{")
        lines.append("\n".join([f"    \"{source}\"" for source, _ in shaders]))
        lines.append("};")
        lines.append("")
        lines.append(f"#endif //{macro}")
        lines.append("")

        f.write("\n".join(lines))


def parse_cmd_args():
    parser = argparse.ArgumentParser()

    parser.add_argument("shaders", nargs="+", help="Shader source files (formatted as: relative,absolute)")
    parser.add_argument("-o", "--output", required=True, help="Output file to put shader list into (must be a .h or .hpp file)")
    parser.add_argument("-m", "--macro", help="Macro to wrap contents within (to distinguish between build types)")

    logger_register_cmd_args(parser)

    args = parser.parse_args()

    logger_parse_cmd_args(parser, args)

    return parser, args


def main():
    parser, args = parse_cmd_args()

    shaders = [pair.split(",") for pair in args.shaders]
    outfile = args.output
    macro   = args.macro

    outdir = os.path.split(outfile)[0]

    logger_info(f"Creating shader-list for {len(shaders)} shaders")
    logger_trace(f"Outputting shader-list in {outfile}")

    if not os.path.exists(outdir):
        os.makedirs(outdir)

    create_shader_list(outfile, shaders, macro)


if __name__ == "__main__":
    main()
