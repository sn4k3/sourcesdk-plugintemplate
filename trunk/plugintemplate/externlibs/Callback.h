//  Callback.h

#if !defined(CALLBACK_H)
#define CALLBACK_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

class cCallback
{
	public:
		virtual bool Execute0() const =0;
		virtual bool Execute1(void *Param) const =0;
		virtual bool Execute2(void *sender, void *Param) const =0;
		virtual bool Execute3(void *sender, void *Param, CUtlVector<void *>* Param2) const =0;
		virtual bool Execute4(void *sender, void *Param, CUtlVector<void *>* Param2, CUtlVector<void *>* Param3) const =0;
		virtual bool Execute5(void *sender, void *Param, CUtlVector<void *>* Param2, CUtlVector<void *>* Param3, int Param4) const =0;
};


template <class cInstance>
class TCallback : public cCallback // Inheriting
{
	public:
		TCallback() // constructor
		{
			// Important : zeroing the pointer so we later can check for errors
			pFunction0 = 0;
			pFunction1 = 0;
			pFunction2 = 0;
			pFunction3 = 0;
			pFunction4 = 0;
			pFunction5 = 0;
		}

		~TCallback()
		{
			pFunction0 = 0;
			pFunction1 = 0;
			pFunction2 = 0;
			pFunction3 = 0;
			pFunction4 = 0;
			pFunction5 = 0;
		}

		// (You can change the callback to take more parameters or to return something)
		typedef bool (cInstance::*tFunction0)();
		typedef bool (cInstance::*tFunction1)(void *Param);
		typedef bool (cInstance::*tFunction2)(void *sender, void *Param);
		typedef bool (cInstance::*tFunction3)(void *sender, void *Param, CUtlVector<void *>* Param2);
		typedef bool (cInstance::*tFunction4)(void *sender, void *Param, CUtlVector<void *>* Param2, CUtlVector<void *>* Param3);
		typedef bool (cInstance::*tFunction5)(void *sender, void *Param, CUtlVector<void *>* Param2, CUtlVector<void *>* Param3, int Param4);

		// Execute the Callback
		virtual bool Execute0() const 
		{
			if (pFunction0) return (cInst->*pFunction0)();
			//else printf("ERROR : the callback function has not been defined !!!!");
			// an undefined callback function will crash the program if you don't check here !
			return false;
		}

		virtual bool Execute1(void *Param) const 
		{
			if (pFunction1) return (cInst->*pFunction1)(Param);
			//else printf("ERROR : the callback function has not been defined !!!!");
			// an undefined callback function will crash the program if you don't check here !
			return false;
		}

		virtual bool Execute2(void *sender, void *Param) const 
		{
			if (pFunction2) return (cInst->*pFunction2)(sender, Param);
			//else printf("ERROR : the callback function has not been defined !!!!");
			// an undefined callback function will crash the program if you don't check here !
			return false;
		}
		
		// Execute the Callback
		virtual bool Execute3(void *sender, void *Param, CUtlVector<void *>* Param2) const 
		{
			if (pFunction3) return (cInst->*pFunction3)(sender, Param, Param2);
			//else printf("ERROR : the callback function has not been defined !!!!");
			// an undefined callback function will crash the program if you don't check here !
			return false;
		}

		// Execute the Callback
		virtual bool Execute4(void *sender, void *Param, CUtlVector<void *>* Param2, CUtlVector<void *>* Param3) const 
		{
			if (pFunction4) return (cInst->*pFunction4)(sender, Param, Param2, Param3);
			//else printf("ERROR : the callback function has not been defined !!!!");
			// an undefined callback function will crash the program if you don't check here !
			return false;
		}

		// Execute the Callback
		virtual bool Execute5(void *sender, void *Param, CUtlVector<void *>* Param2, CUtlVector<void *>* Param3, int Param4) const 
		{
			if (pFunction5) return (cInst->*pFunction5)(sender, Param, Param2, Param3, Param4);
			//else printf("ERROR : the callback function has not been defined !!!!");
			// an undefined callback function will crash the program if you don't check here !
			return false;
		}

		// Set or change the Callback
		void SetCallback0 (cInstance  *cInstancePointer, 
						  tFunction0   pFunctionPointer)
		{
			cInst     = cInstancePointer;
			pFunction0 = pFunctionPointer;
		}

		// Set or change the Callback
		void SetCallback1 (cInstance  *cInstancePointer, 
						  tFunction1   pFunctionPointer)
		{
			cInst     = cInstancePointer;
			pFunction1 = pFunctionPointer;
		}

		// Set or change the Callback
		void SetCallback2 (cInstance  *cInstancePointer, 
						  tFunction2   pFunctionPointer)
		{
			cInst     = cInstancePointer;
			pFunction2 = pFunctionPointer;
		}

		// Set or change the Callback
		void SetCallback3 (cInstance  *cInstancePointer, 
						  tFunction3   pFunctionPointer)
		{
			cInst     = cInstancePointer;
			pFunction3 = pFunctionPointer;
		}

				// Set or change the Callback
		void SetCallback4 (cInstance  *cInstancePointer, 
						  tFunction4   pFunctionPointer)
		{
			cInst     = cInstancePointer;
			pFunction4 = pFunctionPointer;
		}

				// Set or change the Callback
		void SetCallback5 (cInstance  *cInstancePointer, 
						  tFunction5   pFunctionPointer)
		{
			cInst     = cInstancePointer;
			pFunction5 = pFunctionPointer;
		}

	private:
		cInstance  *cInst;
		tFunction0  pFunction0;
		tFunction1  pFunction1;
		tFunction2  pFunction2;
		tFunction3  pFunction3;
		tFunction4  pFunction4;
		tFunction5  pFunction5;
};

#endif // CALLBACK_H




