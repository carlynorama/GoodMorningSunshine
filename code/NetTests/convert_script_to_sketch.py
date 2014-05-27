#!/usr/bin/env python
#
# convert_script_to_sketch.py
#   -- convert a script to code for use in an Yun sketch
# 
# invoke it with something like:
# ./convert_script.py goodmorning_get.py > goodmorning_get_script.h
#

import sys
import os

exename = os.path.basename(sys.argv[0])
if len(sys.argv) != 2 :
    print 'usage: '+ exename + ' <filename>'
    sys.exit(1)

filename = sys.argv[1]
(name,ext) = os.path.splitext(os.path.basename(filename))

outfilename = 'script_'+name+'.h'
print "creating '"+outfilename+ "' from input file '"+filename +"'"

of = open( outfilename, 'w' )

namepath = name + '_path'

of.write( "// \n")
of.write( "// generated by '"+exename+' '+ filename +"'\n")
of.write( "// \n")

of.write( '#define '+namepath+ '"/tmp/'+filename+'"'+"\n")

of.write( "// executes the script\n")
of.write( "void runScript_"+ name +"() {  \n")
of.write( "  Process p;  \n")
of.write( "  p.begin( "+namepath+" ); \n")
of.write( "  p.run(); \n")
of.write( "} \n")

of.write("// checks if script is present\n")
of.write("boolean checkScriptExists_"+ name +"() {  \n")
of.write("  return FileSystem.exists( "+namepath+ "); \n")
of.write("}\n")

of.write( "// upload the script \n")
of.write( "void uploadScript_"+ name +"() { \n")
of.write( "  File f = FileSystem.open( "+ namepath +", FILE_WRITE); \n")

f = open( filename )
for line in f:
    of.write( '  f.print(F( "' + line.rstrip() + '\\n" ));' +"\n")
f.close()

of.write( "  f.close(); \n")
of.write( "  // make executable \n")
of.write( "  Process chmod; \n")
of.write( '  chmod.runShellCommand("chmod +x /tmp/'+filename+'");' +"\n")
of.write( "} \n")

of.close()

