; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CProcess01Dlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Process01.h"

ClassCount=3
Class1=CProcess01App
Class2=CProcess01Dlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PROCESS01_DIALOG
Resource4=IDR_MENU1

[CLS:CProcess01App]
Type=0
HeaderFile=Process01.h
ImplementationFile=Process01.cpp
Filter=N

[CLS:CProcess01Dlg]
Type=0
HeaderFile=Process01Dlg.h
ImplementationFile=Process01Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST2

[CLS:CAboutDlg]
Type=0
HeaderFile=Process01Dlg.h
ImplementationFile=Process01Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROCESS01_DIALOG]
Type=1
Class=CProcess01Dlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST2,SysListView32,1350631424
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_MENUITEM32771
Command2=ID_MENUITEM32772
Command3=ID_MENUITEM32773
CommandCount=3

