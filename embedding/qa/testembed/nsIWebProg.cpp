/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: NPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   David Epstein <depstein@netscape.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the NPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

// nsiWebProg.cpp : implementation file
//

#include "Stdafx.h"
#include "TestEmbed.h"
#include "nsIWebProg.h"
#include "Tests.h"
#include "QaUtils.h"
#include "BrowserFrm.h"
#include "BrowserImpl.h"
#include "BrowserView.h"
#include "domwindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CnsiWebProg

// constructor for CnsiWebProg
CnsiWebProg::CnsiWebProg(nsIWebBrowser *mWebBrowser, 
						 CBrowserImpl *mpBrowserImpl)
{
	qaWebBrowser = mWebBrowser;
	qaBrowserImpl = mpBrowserImpl;
}

// destructor for CnsiWebProg
CnsiWebProg::~CnsiWebProg()
{
}

	// nsIWebProgress test cases

		// get webProg object
nsIWebProgress * CnsiWebProg::GetWebProgObject()
{
	nsCOMPtr<nsIInterfaceRequestor> qaIReq(do_QueryInterface(qaWebBrowser));
	nsCOMPtr<nsIWebProgress> qaWebProgress(do_GetInterface(qaIReq));
	if (!qaWebProgress) {
		QAOutput("Didn't get web progress object.", 2);
		return NULL;
	}
	else {
		QAOutput("We got web progress object.", 1);
		return (qaWebProgress);
	}
}

void CnsiWebProg::AddWebProgLstnr()
{
			// addWebProgListener
	nsCOMPtr<nsIWebProgress> qaWebProgress;
	qaWebProgress = GetWebProgObject();
	nsCOMPtr<nsIWebProgressListener> listener(NS_STATIC_CAST(nsIWebProgressListener*, qaBrowserImpl));
	rv = qaWebProgress->AddProgressListener(listener, nsIWebProgress::NOTIFY_ALL);
	RvTestResult(rv, "nsIWebProgress::AddProgressListener() test", 2);
}

void CnsiWebProg::RemoveWebProgLstnr()
{
		// removeWebProgListener
	nsCOMPtr<nsIWebProgress> qaWebProgress;
	qaWebProgress = GetWebProgObject();
	nsCOMPtr<nsIWebProgressListener> listener(NS_STATIC_CAST(nsIWebProgressListener*, qaBrowserImpl));
	rv = qaWebProgress->RemoveProgressListener(listener);
	RvTestResult(rv, "nsIWebProgress::RemoveProgressListener() test", 2);
}

void CnsiWebProg::GetTheDOMWindow()
{
		// getTheDOMWindow
	nsCOMPtr<nsIWebProgress> qaWebProgress;
	qaWebProgress = GetWebProgObject();
	nsCOMPtr<nsIDOMWindow> qaDOMWindow;
	rv = qaWebProgress->GetDOMWindow(getter_AddRefs(qaDOMWindow));
	if (!qaWebProgress)
		QAOutput("Didn't get DOM Window object.", 2);
	else
		RvTestResult(rv, "nsIWebProgress::GetDOMWindow() test", 2);
}

void CnsiWebProg::OnStartTests(UINT nMenuID)
{
	switch(nMenuID)
	{
		case ID_INTERFACES_NSIWEBPROGRESS_RUNALLTESTS :
			RunAllTests();
			break ;
		case ID_INTERFACES_NSIWEBPROGRESS_ADDPROGRESSLISTENER :
			AddWebProgLstnr();
			break ;
		case ID_INTERFACES_NSIWEBPROGRESS_REMOVEPROGRESSLISTENER :
			RemoveWebProgLstnr();
			break ;
		case ID_INTERFACES_NSIWEBPROGRESS_GETDOMWINDOW  :
			GetTheDOMWindow();
			break ;
	}
}

void CnsiWebProg::RunAllTests(void)
{
	AddWebProgLstnr();
	RemoveWebProgLstnr();
	GetTheDOMWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CnsiWebProg message handlers
