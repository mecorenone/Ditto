// DatabaseUtilites.h: interface for the CDatabaseUtilites class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASEUTILITES_H__039F53EB_228F_4640_8009_3D2B1FF435D4__INCLUDED_)
#define AFX_DATABASEUTILITES_H__039F53EB_228F_4640_8009_3D2B1FF435D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DEFAULT_DB_NAME "DittoDB.mdb"

class CDaoTableDefEx : public CDaoTableDef
{
public:
	CDaoTableDefEx(CDaoDatabase* pDatabase)
		:CDaoTableDef(pDatabase)
	{
	}

	BOOL CreateIndex(BOOL bPrimaryKey, CString csField)
	{
		try
		{
			CDaoIndexInfo IndexInfo;
			CDaoIndexFieldInfo IndexFieldInfo[1];
			IndexFieldInfo[0].m_strName = csField;
			IndexFieldInfo[0].m_bDescending = TRUE;
			IndexInfo.m_strName = csField;
			IndexInfo.m_pFieldInfos = IndexFieldInfo;
			IndexInfo.m_nFields = 1;
			IndexInfo.m_bPrimary = bPrimaryKey;
			IndexInfo.m_bUnique = FALSE;
			IndexInfo.m_bIgnoreNulls = FALSE;
			IndexInfo.m_bRequired = FALSE;

			CDaoTableDef::CreateIndex( IndexInfo );
		}
		catch(CDaoException *e)
		{
			ASSERT(FALSE);
			e->Delete();
			return FALSE;
		}

		return TRUE;
	}

	BOOL CreateField(LPCTSTR lpszName, short nType, long lSize, long lAttributes = 0, CString csDefault = "")
	{
		try
		{
			CDaoFieldInfo fieldinfo;

			// Initialize everything so only correct properties will be set
			fieldinfo.m_strName = lpszName;
			fieldinfo.m_nType = nType;
			fieldinfo.m_lSize = lSize;
			fieldinfo.m_lAttributes = lAttributes;
			fieldinfo.m_nOrdinalPosition = 0;
			fieldinfo.m_bRequired = FALSE;
			fieldinfo.m_bAllowZeroLength = FALSE;
			fieldinfo.m_lCollatingOrder = 0;
			fieldinfo.m_strDefaultValue = csDefault;

			CDaoTableDef::CreateField(fieldinfo);

			return TRUE;
		}
		catch(CDaoException *e)
		{
			e->Delete();
			ASSERT(FALSE);
		}

	return FALSE;
		
	}


	
};

CString GetDBName();
BOOL CompactDatabase();
CString GetDefaultDBName();
BOOL RepairDatabase();
BOOL CheckDBExists(CString csDBPath);
BOOL RemoveOldEntries();
BOOL CreateDB(CString csPath);
BOOL ValidDB(CString csPath);
BOOL EnsureDirectory(CString csPath);

#endif // !defined(AFX_DATABASEUTILITES_H__039F53EB_228F_4640_8009_3D2B1FF435D4__INCLUDED_)