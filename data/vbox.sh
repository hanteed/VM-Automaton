#!/bin/bash
VBoxManage registervm data/VM/VM.vbox  
VBoxManage clonevm VM --name=$1 --register --mode=all --options=keepallmacs --options=keepdisknames --options=keephwuuids
VBoxManage unregistervm VM

VBoxManage modifyvm $1 --memory $2 --vram $3
VBoxManage modifyvm $1 --cpus $3
VBoxManage startvm $1