/* 

                          Firewall Builder

                 Copyright (C) 2008 NetCitadel, LLC

  Author:  Vadim Kurland     vadim@vk.crocodile.org

  $Id: UserService.cpp 35 2008-04-26 19:13:33Z vadim $


  This program is free software which we release under the GNU General Public
  License. You may redistribute and/or modify this program under the terms
  of that license as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 
  To get a copy of the GNU General Public License, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/


#include <assert.h>

#include <fwbuilder/libfwbuilder-config.h>

#include <fwbuilder/UserService.h>
#include <fwbuilder/XMLTools.h>

using namespace std;
using namespace libfwbuilder;

const char *UserService::TYPENAME={"UserService"};

UserService::UserService() {}
UserService::UserService(const FWObject *root, bool prepopulate) :
    Service(root, prepopulate) {}
UserService::~UserService() {}


FWObject& UserService::shallowDuplicate(const FWObject *x,
                                        bool preserve_id) throw(FWException)
{
    const UserService *cs = dynamic_cast<const UserService *>(x);
    userid = cs->userid;
    return FWObject::shallowDuplicate(x, preserve_id);
}

void UserService::fromXML(xmlNodePtr root) throw(FWException)
{
    FWObject::fromXML(root);

    const char *n = FROMXMLCAST(xmlGetProp(root,TOXMLCAST("userid")));
    if(n)
    {
        userid = string(n);
        FREEXMLBUFF(n);
    }
}

xmlNodePtr UserService::toXML(xmlNodePtr parent) throw(FWException)
{
    xmlNodePtr me = FWObject::toXML(parent);
    xmlNewProp(me, TOXMLCAST("userid"), STRTOXMLCAST(userid));
    return me;
}

bool UserService::cmp(const FWObject *obj) throw(FWException)
{
    if (UserService::constcast(obj)==NULL) return false;
    if (!FWObject::cmp(obj)) return false;
    
    const UserService *user_serv = UserService::constcast(obj);
    return (userid == user_serv->userid);
}

