@call "%VS100COMNTOOLS%\vsvars32.bat"

@echo "�������¹���YDWE��%1|Win32"
@echo "�������¹���YDWE��%1|Win32" >> %2
devenv YDWE.sln /Rebuild "%1|Win32" /out %2

@echo "�������¹���YDColorizer��%1|Any CPU"
@echo "�������¹���YDColorizer��%1|Any CPU" >> %2
devenv ../../Plugin/YDColorizer/YDColorizer.sln /Rebuild "%1|Any CPU" /out %2

@echo "�������¹���YDUI��YDWE|Win32"
@echo "�������¹���YDUI��YDWE|Win32" >> %2
devenv ../../UI/sln/YDUI.sln /Rebuild "YDWE|Win32" /out %2

@echo "�������¹���YDUI��YDTrigger|Win32"
@echo "�������¹���YDUI��YDTrigger|Win32" >> %2
devenv ../../UI/sln/YDUI.sln /Rebuild "YDTrigger|Win32" /out %2

@echo "����UI��binĿ¼"
@echo "����UI��binĿ¼" >> %2
xcopy ..\..\UI\bin ..\..\Build\bin\%1\share\mpq\ /d /y /e >> %2

@echo "���ɲ��ֺ��������"
@echo "���ɲ��ֺ��������" >> %2
"..\..\..\..\..\..\OpenSource\Python\2.7.2\python.exe" "..\Script\anti_bj_leak_make.py" ..\Script\bj_script.j ..\..\Build\bin\%1\jass\AntiBJLeak\