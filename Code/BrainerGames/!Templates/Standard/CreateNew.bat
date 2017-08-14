set name=WordReduce

cd..
cd..
mkdir %name%
copy .\!Templates\Standard\BGame_Template.bdsproj .\%name%\BGame_%name%.bdsproj
copy .\!Templates\Standard\BGame_Template.bpf .\%name%\BGame_%name%.bpf
copy .\!Templates\Standard\BGame_Template.res .\%name%\BGame_%name%.res
copy .\!Templates\Standard\MainGame.cpp .\%name%\MainGame.cpp
copy .\!Templates\Standard\MainGame.h .\%name%\MainGame.h

cd !Templates

gfind ..\%name%\BGame_%name%.bdsproj /S:"Template" /R:"%name%" 
gfind ..\%name%\MainGame.cpp /S:"Template" /R:"%name%" 
