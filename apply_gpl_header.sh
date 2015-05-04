#!/bin/bash
header=$1
shift
for file in $*
do
  firstline=`head -n 1 $file `
  if test "$firstline" = "// -*- C++ -*-" 
      then
      echo $firstline >> file.tmp
      cat $header >> file.tmp
      sed 's|// -\*- C++ -\*-||' $file >> file.tmp
  else
      cat $header $file >> file.tmp
  fi
  mv file.tmp $file
done
