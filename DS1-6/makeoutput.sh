#!/bin/bash
files=( 10001 601 602 603 604 605 )
range=10
output=( stdout_task1.txt stdout_task2.txt stdout_task3.txt )
testingProgram="$1"

command_quit="0"
command_load="1"
command_range="2"
command_remove="3"

# doCommands $tasknumber $command
function doCommands()
{
    local stdin=$2
    stdin="$stdin $command_quit"
    echo $stdin| $testingProgram >> "${output[$1]}"
}


function testTask1()
{
    local fileid=$1
    local stdin=""

    # load file
    stdin="$stdin $command_load $fileid"

    doCommands 0 "$stdin"
}

function testTask2()
{
    local fileid=$1
    local stdin=""
    local i=0

    for i in $range
    do
        # load file
        stdin="$stdin $command_load $fileid"

        # show range
        stdin="$stdin $command_range $i"

        doCommands 1 "$stdin"
    done
}

function testTask3()
{
    local fileid=$1
    local stdin=""

    # load file
    stdin="$stdin $command_load $fileid"

    # remove max
    for dotimes in $(seq 1 $lineNumber)
    do
        # remove node
        stdin="$stdin $command_remove"
    done

    doCommands 2 "$stdin"
}

rm ${output[*]}
for i in "${files[@]}"
do
    filename="input$i.txt"
    lineNumber=$(($(wc $filename| awk '{ print $1 }')-1))

    testTask1 $i
    testTask2 $i
    testTask3 $i

done
echo testing program: \"$testingProgram\"

