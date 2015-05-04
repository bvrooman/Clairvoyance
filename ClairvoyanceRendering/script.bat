set SolutionDir=%1
set ProjectDir=%2
set Configuration=%3
set Platform=%4

xcopy /Y /d %ProjectDir%Assimp\%Platform%\%Configuration%\* %SolutionDir%%Platform%\%Configuration%\
