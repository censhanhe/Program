#ifndef		__PROM_DIRECTIONAL_FREELINK_H__
#define		__PROM_DIRECTIONAL_FREELINK_H__

namespace PROM
{
	template<typename _DataType> class DirectionalFreeLink : public GAIA::RefObject
	{
	public:
		typedef DirectionalFreeLink<_DataType> __MyType;
	public:
		GINL GAIA::BL BindNext(__MyType* p)
		{
			GAIA_AST(p != GNULL);
			if(p == GNULL)
				return GAIA::False;
			GAIA_AST(p != this);
			if(p == this)
				return GAIA::False;
			if(this->prev_exist(p))
				return GAIA::False;
			if(this->next_exist(p))
				return GAIA::False;
			this->Reference();
			p->Reference();
			GAIA::BL bExist = GAIA::False;
			for(GAIA::SIZE x = 0; x < m_nexts.size(); ++x)
			{
				if(m_nexts[x] == GNULL)
				{
					m_nexts[x] = p;
					bExist = GAIA::True;
					break;
				}
			}
			if(!bExist)
				m_nexts.push_back(p);
			bExist = GAIA::False;
			for(GAIA::SIZE x = 0; x < p->m_prevs.size(); ++x)
			{
				if(p->m_prevs[x] == GNULL)
				{
					p->m_prevs[x] = this;
					bExist = GAIA::True;
					break;
				}
			}
			if(!bExist)
				p->m_prevs.push_back(this);
			return GAIA::True;
		}
		GINL GAIA::BL UnbindNext(__MyType* p)
		{
			GAIA_AST(p != GNULL);
			if(p == GNULL)
				return GAIA::False;
			GAIA_AST(p != this);
			if(p == this)
				return GAIA::False;
			GAIA::BL bExist = GAIA::False;
			for(GAIA::SIZE x = 0; x < m_nexts.size(); ++x)
			{
				if(m_nexts[x] == p)
				{
					m_nexts[x] = GNULL;
					bExist = GAIA::True;
					break;
				}
			}
			if(!bExist)
				return GAIA::False;
			bExist = GAIA::False;
			for(GAIA::SIZE x = 0; x < p->m_prevs.size(); ++x)
			{
				if(p->m_prevs[x] == this)
				{
					p->m_prevs[x] = GNULL;
					bExist = GAIA::True;
					break;
				}
			}
			if(!bExist)
			{
				GAIA_AST(GAIA::ALWAYSFALSE);
				return GAIA::False;
			}
			this->Release();
			p->Release();
			return GAIA::True;
		}
		GINL GAIA::GVOID UnbindNextAll()
		{
			for(GAIA::SIZE x = 0; x < m_nexts.size(); ++x)
			{
				__MyType* pPLC = m_nexts[x];
				if(pPLC == GNULL)
					continue;
				this->UnbindNext(pPLC);
			}
		}
		GINL GAIA::SIZE GetNextSize() const{return m_nexts.size();}
		GINL __MyType* GetNext(const GAIA::SIZE& index) const
		{
			if(index >= m_nexts.size())
				return GNULL;
			if(m_nexts[index] == GNULL)
				return GNULL;
			m_nexts[index]->Reference();
			return m_nexts[index];
		}
		GINL GAIA::BL BindPrev(__MyType* p){return p->BindNext(this);}
		GINL GAIA::BL UnbindPrev(__MyType* p){return p->UnbindNext(this);}
		GINL GAIA::GVOID UnbindPrevAll()
		{
			for(GAIA::SIZE x = 0; x < this->GetPrevSize(); ++x)
			{
				__MyType* pPLC = m_prevs[x];
				if(pPLC == GNULL)
					continue;
				this->UnbindPrev(pPLC);
			}
		}
		GINL GAIA::SIZE GetPrevSize() const{return m_prevs.size();}
		GINL __MyType* GetPrev(const GAIA::SIZE& index) const
		{
			if(index >= m_prevs.size())
				return GNULL;
			if(m_prevs[index] == GNULL)
				return GNULL;
			m_prevs[index]->Reference();
			return m_prevs[index];
		}
	private:
		GINL GAIA::BL next_exist(__MyType* p) const
		{
			GAIA_AST(p != GNULL);
			if(p == GNULL)
				return GAIA::False;
			for(GAIA::SIZE x = 0; x < this->GetNextSize(); ++x)
			{
				__MyType* pNext = this->GetNext(x);
				if(pNext == GNULL)
					continue;
				if(pNext == p)
				{
					pNext->Release();
					return GAIA::True;
				}
				if(pNext->next_exist(p))
				{
					pNext->Release();
					return GAIA::True;
				}
				pNext->Release();
			}
			return GAIA::False;
		}
		GINL GAIA::BL prev_exist(__MyType* p) const
		{
			GAIA_AST(p != GNULL);
			if(p == GNULL)
				return GAIA::False;
			for(GAIA::SIZE x = 0; x < this->GetPrevSize(); ++x)
			{
				__MyType* pPrev = this->GetPrev(x);
				if(pPrev == GNULL)
					continue;
				if(pPrev == p)
				{
					p->Release();
					return GAIA::True;
				}
				if(pPrev->prev_exist(p))
				{
					pPrev->Release();
					return GAIA::True;
				}
				pPrev->Release();
			}
			return GAIA::False;
		}
	protected:
		virtual GAIA::GVOID Destruct()
		{
			this->UnbindNextAll();
			this->UnbindPrevAll();
		}
	private:
		typedef GAIA::CONTAINER::Vector<__MyType*> __DoubleLinkList;
	private:
		__DoubleLinkList m_nexts;
		__DoubleLinkList m_prevs;
	};
};

#endif
