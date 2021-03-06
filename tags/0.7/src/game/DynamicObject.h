/* 
 * Copyright (C) 2005,2006,2007 MaNGOS <http://www.mangosproject.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef MANGOSSERVER_DYNAMICOBJECT_H
#define MANGOSSERVER_DYNAMICOBJECT_H

#include "Object.h"

class Unit;
struct SpellEntry;

class DynamicObject : public WorldObject
{
    public:
        typedef std::set<Unit*> AffectedSet;
        DynamicObject( WorldObject *instantiator );

        bool Create(uint32 guidlow, Unit *caster, uint32 spellId, uint32 effIndex, float x, float y, float z, int32 duration, float radius);
        void Update(uint32 p_time);
        void Delete();
        uint32 GetSpellId() const { return m_spellId; }
        uint32 GetEffIndex() const { return m_effIndex; }
        uint32 GetDuration() const { return m_aliveDuration; }
        uint64 GetCasterGUID() const { return m_casterGuid; }
        Unit* GetCaster() const;
        float GetRadius() const { return m_radius; }
        bool IsAffecting(Unit *unit) const { return m_affected.find(unit) != m_affected.end(); }
        void AddAffected(Unit *unit) { m_affected.insert(unit); }
        void RemoveAffected(Unit *unit) { m_affected.erase(unit); }
        void Delay(int32 delaytime);
        bool isVisibleForInState(Player const* u, bool inVisibleList) const;
    protected:
        uint64 m_casterGuid;
        uint32 m_spellId;
        uint32 m_effIndex;
        int32 m_aliveDuration;
        time_t m_nextThinkTime;
        float m_radius;
        AffectedSet m_affected;
};
#endif
