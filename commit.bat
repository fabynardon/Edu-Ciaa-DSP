@echo OFF
set SVN_EDITOR=TYPE
set /P mensaje=Mensaje del Commit:
svn commit  -m "%%mensaje%%" --username fabian_nardone@hotmail.com