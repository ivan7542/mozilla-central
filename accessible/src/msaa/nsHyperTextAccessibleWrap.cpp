/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim:expandtab:shiftwidth=2:tabstop=2:
 */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Mozilla Foundation.
 * Portions created by the Initial Developer are Copyright (C) 2007
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Alexander Surkov <surkov.alexander@gmail.com> (original author)
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include "nsHyperTextAccessibleWrap.h"

nsString nsHyperTextAccessibleWrap::sText;
PRInt32 nsHyperTextAccessibleWrap::sOffset = 0;
PRUint32 nsHyperTextAccessibleWrap::sLength = 0;
PRBool nsHyperTextAccessibleWrap::sIsInserted = PR_FALSE;

NS_IMPL_ISUPPORTS_INHERITED0(nsHyperTextAccessibleWrap,
                             nsHyperTextAccessible)

IMPL_IUNKNOWN_INHERITED2(nsHyperTextAccessibleWrap,
                         nsAccessibleWrap,
                         CAccessibleHypertext,
                         CAccessibleEditableText);

NS_IMETHODIMP
nsHyperTextAccessibleWrap::FireAccessibleEvent(nsIAccessibleEvent *aEvent)
{
  PRUint32 eventType;
  aEvent->GetEventType(&eventType);

  if (eventType == nsIAccessibleEvent::EVENT_TEXT_CHANGED) {
    nsCOMPtr<nsIAccessibleTextChangeEvent> textEvent(do_QueryInterface(aEvent));
    NS_ENSURE_STATE(textEvent);

    textEvent->GetStart(&sOffset);
    textEvent->GetLength(&sLength);
    textEvent->IsInserted(&sIsInserted);

    GetText(sOffset, sOffset + sLength, sText);
  }

  return nsHyperTextAccessible::FireAccessibleEvent(aEvent);
}

nsresult
nsHyperTextAccessibleWrap::GetModifiedText(PRBool aGetInsertedText,
                                           nsAString& aText,
                                           PRUint32 *aStartOffset,
                                           PRUint32 *aEndOffset)
{
  if ((aGetInsertedText && sIsInserted) || (!aGetInsertedText && !sIsInserted)) {
    aText.Assign(sText);
    *aStartOffset = sOffset;
    *aEndOffset = sOffset + sLength;
  } else {
    aText.Truncate();
    *aStartOffset = 0;
    *aEndOffset = 0;
  }

  return NS_OK;
}

