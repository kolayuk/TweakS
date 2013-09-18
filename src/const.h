/*
 * const.h
 *
 *  Created on: 07.07.2010
 *      Author: mvideo
 */

#ifndef CONST_H_
#define CONST_H_

const TUint KDefaultIAPSettingKey=0x1;
const TUint KAutoUpdateSettingKey=0x2;


_LIT8(KBuildDate,__DATE__);
_LIT8(KBuildTime,__TIME__);
_LIT8(KVersionInfoURL,"http://kolaysoft.ru/TweakS/update/info.txt");
_LIT8(KCheckUpdateURL,"http://kolaysoft.ru/TweakS/update/version.php");
_LIT8(KDownloadUpdateURL,"http://kolaysoft.ru/TweakS/update/download.php");
_LIT(KUpdatePath,"C:\\Data\\TweakS.sis");
_LIT(KPluginsListURL,"http://kolaysoft.ru/TweakS/update/plugins/plugins.php?lang=%d");
_LIT(KPluginsPathURL,"http://kolaysoft.ru/TweakS/update/plugins/download.php?lang=%d&file=%S");
_LIT(KDisabledPluginsDir,"C:\\System\\Apps\\TweakS\\DisabledPlugins\\");
_LIT(KPluginsDir,"C:\\System\\Apps\\TweakS\\Plugins\\");
_LIT(KIniMask,"*.plg");
_LIT(KCREPath,"c:\\private\\10202be9\\persists\\");
_LIT(KCREExtension,".cre");
_LIT(KSysApProcessUID,"100039e3");
_LIT(KTXTPath,"z:\\private\\10202be9\\");
_LIT(KTXTPathC,"C:\\private\\10202be9\\");
_LIT(KTXTExtension,".txt");

_LIT(KSettingsPath,"C:\\System\\Apps\\TweakS\\Plugins\\e9066a16.cre");

#ifdef _DEBUG
_LIT(KCallBackUrl,"http://kolaysoft.ru/comments/add.php?project=TweakS_D&message=");
#else
_LIT(KCallBackUrl,"http://kolaysoft.ru/comments/add.php?project=TweakS&message=");
#endif

#endif /* CONST_H_ */
