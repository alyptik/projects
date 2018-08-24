#!/bin/bash

script="${0##*/}"
binary="${script%.sh}"

trap 'rm -fv -- "./$binary"' INT ERR EXIT

program+='g(i,x,t,o){'
program+='return((3&x&(i*((3&i>>16?"BY}6YB6%":"Qj}6jQ6%")[t%8]+51)>>o))<<4);};'
program+='main(i,n,s){'
program+='for(i=0;;i++){'
program+='putchar(g(i,1,n=i>>14,12)+'
program+='g(i,s=i>>17,n^i>>13,10)+g(i,s/3,n+((i>>11)%3),10)+g(i,s/5,8+n-((i>>10)%3),9));}}'

<<<"$program" gcc -xc - -o "$binary" && "./$binary" | aplay
