#!/bin/bash

open -a Terminal.app -n "tail -f access.log"
open -a Terminal.app -n "tail -f error.log"
open -a Terminal.app -n "tail -f webserv.pid"
