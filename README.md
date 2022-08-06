# ApplyPAP
# a simple way to apply Black Desert .PAP files to a Client

you will need expapply.dll from the Black Desert root folder
it will supply ApplyPAP.exe with the needed DLL imports
expapply.dll is not included in this project!

example use, e.g. PowerShell:
for ($i=1; $i -le 1000; $i=$i+1 ) { .\ApplyPap.exe .\patch_temp\$i.PAP .; }

Fyyre