#!/bin/zsh
# Jaremy Creechley
# HW1
# CS550

setopt extended_glob
setopt NULL_GLOB

# TODO: initialize test option?
function puts {
   echo -e $space $*
}

function execTest {
   tests=($( echo *.java))
   if [[ $tests == "" ]]; then
      puts "no tests found"
   fi
   for tst in $tests; do
      t=$tst:r
      puts "executing " $t
      # TODO: check that expect files are present
      if [[ -f $t.stdout.expect ]] && [[ -f $t.stderr.expect ]]; then
         echo "initialized"
         ($program < $tst 1> $t.stdout.run 2> $t.stderr.run)
         puts "Comparing STDOUT:"
         diff $t.stdout.expect $t.stdout.run
         err=$?
         if [[ $err != 0 ]]; then
            ERROR=$err
         fi 
         puts "Comparing STDERR:"
         diff $t.stderr.expect $t.stderr.run
         err=$?
         if [[ $err != 0 ]]; then
            ERROR=$err
         fi 
         
      else
         echo "initializing..."
         echo program: $program pwd: $(pwd)
         echo "$program < $tst 1> $t.stdout.expect 2> $t.stderr.expect"
         ($program < $tst 1> $t.stdout.expect 2> $t.stderr.expect)
      fi
      # TODO: run test command with input
   done  
}

function subTest {
   # puts -e "Running: " $2.$1
   TestSuite $*
}


function TestSuite {
   ts=""   
   suite=$1
   2=${2:+"$2::"}$1
   if [[ $suite != "" ]]; then
      # puts -e "TestSuite:" $suite 
      echo "\n--------------------------------------------------------"
      echo "Suite:" $2
      echo "--------------------------------------------------------"
      cd $suite
   fi
   
   execTest $suite
   
   tdirs=($( echo Test* ) )
   
   if [[ $#tdirs != 0 ]]; then
      
      # puts "Found Test Suites: $tdirs"
      # find any sub test dirs
      for ts in $tdirs; do
         subTest $ts $2
      done
   fi
   
   cd ..

}

program="/Users/jaremy/proj/comp/trans/generate"
space=""
puts "Tester\n=========================================================="
TestSuite
puts "pwd" $(pwd)
echo ERROR $ERROR
exit $ERROR