import os, sys
from SCons.Script.SConscript import SConsEnvironment

def ExtendPaths ( base, extra_dirs ):
  return [ os.path.join ( base, extra ) for extra in ( extra_dirs )]
  
class BuildConfig:
  def __init__(self, ARGUMENTS):
    self.Mode = ARGUMENTS.get('mode', 'release')
    if not (self.Mode in ['debug', 'release']):
       print "Error: expected 'debug' or 'release', found: " + Mode
       Exit(1)
    self.Platform = ARGUMENTS.get('platform', 'windows')
    if not (self.Platform in ['windows', 'linux']):
       print "Error: expected 'windows' or 'linux', found: " + Platform
       Exit(1)
    print 'Mode =', self.Mode
    print 'Platform =', self.Platform

  def CreateVCEnvironment(self,env):
    env = env.Clone()  
    if self.Mode == 'release':
      env.Append ( CPPDEFINES=[ 'NDEBUG' ] )
    else:
      env.Append ( CPPDEFINES=[ 'DEBUG', '_DEBUG' ] )
    env.Append ( CPPDEFINES =
                  [ '_CRT_NONSTDC_NO_DEPRECATE',
                    '_CRT_SECURE_NO_WARNINGS',
                    '_SCL_SECURE_NO_WARNINGS',
                    '_SECURE_SCL=0',
                    '_HAS_ITERATOR_DEBUGGING=0'
                  ]
               )
    env.Append ( CPPFLAGS='/EHsc /W3'.split(' ') )
    if self.Mode == 'release':
      env.Append ( CPPFLAGS='/O2 /GF /MD /Gy /Ob1'.split(' ') )
    else:
      env.Append ( CPPFLAGS='/Od /RTC1 /MDd'.split(' ') )

    env.Append ( CPPDEFINES =
                  [ '_WINDOWS',
                    'WIN32',
                  ]
               )
    return env
    
  def CreateGCCEnvironment(self,env):
    env.Append \
        ( CPPFLAGS =
            [ "-Wall",
              "-Wno-sign-compare",
              "-Wno-switch",
              "-Wno-switch-default",
              "-Wno-parentheses",
              "-pipe",
              "-Wno-invalid-offsetof",
              "-fno-operator-names"
            ]
            +
            # Make some warnings be errors.
            [ "-Werror=" + Warning
              for Warning in
              (
                "return-type",
                "strict-aliasing",
                "sequence-point",
                "reorder",
                # "non-virtual-dtor",  # Good to enable.
                "delete-non-virtual-dtor",
                "empty-body",
              )
            ]
        )
    if self.Mode == 'debug':
      env.Append ( CPPFLAGS= ( '-ggdb', '-g3' ) )
    elif self.Mode == 'release' :
      env.Append ( CPPFLAGS = ( "-O2", ) )
    return env

