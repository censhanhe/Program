#ifndef		__PROM_BASE_H__
#define		__PROM_BASE_H__

namespace PROM
{
	template<typename _RowType, typename _ColType> class BasicTextLocation
	{
	public:
		typedef _RowType _rowtype;
		typedef _ColType _columntype;
	public:
		typedef BasicTextLocation<_RowType, _ColType> __MyType;
	public:
		GINL BasicTextLocation(){this->clear();}
		GINL BasicTextLocation(const _RowType& row, const _ColType& col){this->row(row); this->col(col);}
		GINL BasicTextLocation(const __MyType& src){this->operator = (src);}
		GINL GAIA::GVOID clear(){m_row = m_col = GINVALID;}
		GINL GAIA::GVOID empty() const{if(m_row == GINVALID || m_row == GINVALID) return GAIA::True; return GAIA::False;}
		GINL GAIA::GVOID row(const _RowType& row){m_row = row;}
		GINL const _RowType& row() const{return m_row;}
		GINL GAIA::GVOID col(const _ColType& col){m_col = col;}
		GINL const _ColType& col() const{return m_col;}
		const __MyType& operator = (const __MyType& src)
		{
			m_row = src.m_row;
			m_col = src.m_col;
			return *this;
		}
		GAIA_CLASS_OPERATOR_COMPARE2(m_col, m_col, m_row, m_row, __MyType);
	private:
		_RowType m_row;
		_ColType m_col;
	};
	template<typename _FileIDType, typename _RowType, typename _ColType> class BasicLocation
	{
	public:
		typedef _FileIDType _fileidtype;
		typedef _RowType _rowtype;
		typedef _ColType _columntype;
	public:
		typedef BasicLocation<_FileIDType, _RowType, _ColType> __MyType;
		typedef BasicTextLocation<_RowType, _ColType> __TextLocType;
	public:
		GINL BasicLocation(){this->clear();}
		GINL BasicLocation(const _FileIDType& fileid, const __TextLocType& begin, const __TextLocType& end){this->fileid(fileid); this->begin(begin); this->end(end);}
		GINL BasicLocation(const __MyType& src){this->operator = (src);}
		GINL GAIA::GVOID clear(){m_fileid = GINVALID; m_begin.clear(); m_end.clear();}
		GINL GAIA::GVOID empty() const{if(m_fileid == GINVALID || m_begin.empty() || m_end.empty()) return GAIA::True; return GAIA::False;}
		GINL GAIA::GVOID fileid(const _FileIDType& src){m_fileid = src;}
		GINL const _FileIDType& fileid() const{return m_fileid;}
		GINL GAIA::GVOID begin(const __TextLocType& src){m_begin = src;}
		GINL const __TextLocType& begin() const{return m_begin;}
		GINL GAIA::GVOID end(const __TextLocType& src){m_end = src;}
		GINL const __TextLocType& end() const{return m_end;}
		const __MyType& operator = (const __MyType& src)
		{
			m_fileid = src.m_fileid;
			m_begin = src.m_begin;
			m_end = src.m_end;
			return *this;
		}
		GAIA_CLASS_OPERATOR_COMPARE3(m_fileid, m_fileid, m_begin, m_begin, m_end, m_end, __MyType);
	private:
		_FileIDType m_fileid;
		__TextLocType m_begin;
		__TextLocType m_end;
	};
	typedef BasicTextLocation<GAIA::N32, GAIA::N32> TLoc;
	typedef BasicLocation<GAIA::N32, GAIA::N32, GAIA::N32> Loc;
};

#endif