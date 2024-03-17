import argparse
import os

from tools_common import *

TOOL_GLSLC = {
    DevPlatform.LINUX  : "glslc",
    DevPlatform.WINDOWS: "glslc"
}


def compile_shader_glsl(srcfile, outfile, tempdir, type):
    srcabs  = os.path.realpath(srcfile)

    outspv = outfile

    logger_trace(f"Generating outputs:\nFinal SPIR-V bytecode '{outspv}'")

    run_process(TOOL_GLSLC[get_devplatform()], f"{srcabs}", "-o", f"{outspv}")


def parse_cmd_args():
    parser = argparse.ArgumentParser()

    parser.add_argument("source", help="Shader source file to compile")
    parser.add_argument("-o", "--output", required=True, help="Output file to put bytecode into")
    parser.add_argument("-d", "--temp-output", help="Output directory to put intermediary files into. By default these files will be deleted.")

    platform_register_cmd_args(parser)
    logger_register_cmd_args(parser)

    args = parser.parse_args()

    platform_parse_cmd_args(parser, args)
    logger_parse_cmd_args(parser, args)

    return parser, args


def main():
    parser, args = parse_cmd_args()

    srcfile = args.source
    outfile = args.output
    tempdir = args.temp_output

    outdir = os.path.split(outfile)[0]

    logger_info(f"Compiling shader: '{srcfile}'")
    logger_trace(f"Outputting to directory: '{outfile}'")
    if tempdir:
        logger_info(f"Temp directory specified: '{tempdir}'")

    if not os.path.exists(outdir):
        os.makedirs(outdir)

    extension = os.path.splitext(srcfile)[1]
    if extension == ".vert":
        compile_shader_glsl(srcfile, outfile, tempdir, "vs")
    elif extension == ".frag":
        compile_shader_glsl(srcfile, outfile, tempdir, "fs")
    else:
        logger_fatal(f"Shader format [{extension}] not supported")


if __name__ == "__main__":
    main()
