require conf/distro/poky.conf

DISTRO = "jd2mr-base"
DISTRO_NAME = "Mr Roboto Distro Base"
DISTRO_VERSION = "2.5"

SDK_VENDOR = "-jd2mrsdk"

MAINTAINER = "JD Squared <support@jd2.com>"

TARGET_VENDOR = "-jd2mr"

DISTROOVERRIDES = "jd2mr"

# This function changes the default tune for machines which are based on armv7a
# to use common tune value
def arm_tune_handler(d):
    features = d.getVar('TUNE_FEATURES', True).split()
    if 'armv7a' in features or 'armv7ve' in features:
        tune = 'armv7athf'
        if 'bigendian' in features:
            tune += 'b'
        if 'vfpv3' in features:
            tune += '-vfpv3'
        if 'vfpv3d16' in features:
            tune += '-vfpv3d16'
        if 'neon' in features:
            tune += '-neon'
        if 'vfpv4' in features:
            tune += '-vfpv4'
    else:
        tune = d.getVar('DEFAULTTUNE', True)
    return tune

DEFAULTTUNE_jd2mr := "${@arm_tune_handler(d)}"

DISTRO_ARM_INSTRUCTION ?= "thumb"
DISTRO_ARM_INSTRUCTION_armv5 ?= "arm"
ARM_INSTRUCTION_SET_jd2mr ??= "${DISTRO_ARM_INSTRUCTION}"

# Log information on images and packages
INHERIT += "buildhistory"
BUILDHISTORY_COMMIT = "1"
