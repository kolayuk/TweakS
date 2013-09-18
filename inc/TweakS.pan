
#ifndef TWEAKS_PAN_H
#define TWEAKS_PAN_H

/** TweakS application panic codes */
enum TTweakSPanics
	{
	ETweakSUi = 1
	// add further panics here
	};

inline void Panic(TTweakSPanics aReason)
	{
	_LIT(applicationName,"TweakS");
	User::Panic(applicationName, aReason);
	}

#endif // TWEAKS_PAN_H
