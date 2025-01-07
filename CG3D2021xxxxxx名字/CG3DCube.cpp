#include "pch.h" 
#include "CG3DCube.h" 
#include "CG3DRenderContext.h" 
#include "CG3DCamera.h" 

IMPLEMENT_SERIAL(CG3DCube, CG3DRenderable, 1)

CG3DCube::CG3DCube()
	: CG3DRenderable(CString("CG3DCube")), mSize(1)
{
	mName.Format(_T("������-%ld"), sID);
}
CG3DCube::CG3DCube(double size) //�����߳� 
	: CG3DRenderable(CString("CG3DCube")), mSize(size)
{
	mName.Format(_T("������-%ld"), sID);
}

CG3DCube::CG3DCube(const CG3DCube& other)
	: CG3DRenderable(CString("CG3DCube")), mSize(other.mSize)
{
	mName.Format(_T("������-%ld"), sID);
}

CG3DCube::~CG3DCube()
{
}

//���л� 
void CG3DCube::Serialize(CArchive& ar)
{
	CG3DRenderable::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mSize;
	}
	else
	{
		ar >> mSize;
	}
}

//���ƺ������������ɫ�����
void CG3DCube::Draw(bool outline) {
	double half = mSize / 2; //ģ������ϵ�����������ģ��ߣ��棩��������ƽ�� 

	// ���outlineΪtrue��������ƺ�ɫ���
	if (outline) {
		glColor3f(0.0f, 0.0f, 0.0f); // ������ɫΪ��ɫ
	}
	else {
		// ����Ϊԭʼ��ɫ����
		glColor3f(0.992f, 0.996f, 0.024f); // ��ɫ��Ϊ��ɫ #FDFE06
	}
	glVertex3f(half, half, -half);
	glVertex3f(-half, half, -half);
	glVertex3f(-half, half, half);
	glVertex3f(half, half, half);

	if (!outline) glColor3f(1.0f, 1.0f, 1.0f); // ��ɫ�ĳɰ�ɫ #FFFFFF
	glVertex3f(half, -half, half);
	glVertex3f(-half, -half, half);
	glVertex3f(-half, -half, -half);
	glVertex3f(half, -half, -half);

	if (!outline) glColor3f(0.153f, 0.102f, 0.996f); // ��ɫ��Ϊ��ɫ #271AFE
	glVertex3f(half, half, half);
	glVertex3f(-half, half, half);
	glVertex3f(-half, -half, half);
	glVertex3f(half, -half, half);

	if (!outline) glColor3f(0.431f, 0.992f, 0.000f); // ��ɫ�ĳ���ɫ #6EFD00
	glVertex3f(half, -half, -half);
	glVertex3f(-half, -half, -half);
	glVertex3f(-half, half, -half);
	glVertex3f(half, half, -half);

	if (!outline) glColor3f(0.941f, 0.596f, 0.067f); // ��ɫ�ĳɳ�ɫ #F09811
	glVertex3f(-half, half, half);
	glVertex3f(-half, half, -half);
	glVertex3f(-half, -half, -half);
	glVertex3f(-half, -half, half);

	if (!outline) glColor3f(0.914f, 0.043f, 0.075f); // ��ɫ�ĳɺ�ɫ #E90B13
	glVertex3f(half, half, -half);
	glVertex3f(half, half, half);
	glVertex3f(half, -half, half);
	glVertex3f(half, -half, -half);
}

void CG3DCube::Render(CG3DRenderContext* pRC, CG3DCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return;

	glPushMatrix();
	glMultMatrixd(mMat.ptr());

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	Draw(false); // �������ɫ
	glEnd();

	// ������
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(6.0f); // �����߿�
	glBegin(GL_QUADS);
	Draw(true); // �������
	glEnd();

	glPopMatrix();
}

void CG3DCube::Render(CG3DRenderContext* pRC, CG3DCamera* pCamera, Mat4d pMat)
{
	if (pRC == nullptr || pCamera == nullptr)
		return;

	glPushMatrix();
	glMultMatrixd((pMat*mMat).ptr());

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	Draw(false); // �������ɫ
	glEnd();

	// ������
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(6.0f); // �����߿�
	glBegin(GL_QUADS);
	Draw(true); // �������
	glEnd();

	glPopMatrix();
}

void CG3DCube::computeBoundingBox() //�����Χ�� 
{
	mABox.setNull();  //����� 
	//���ݲ����;�������Χ�� 
	mABox = ABox3d(Vector3<double>(-mSize / 2, -mSize / 2, -mSize / 2), Vector3<double>(mSize / 2, mSize / 2, mSize / 2));
	setBoundsDirty(false);
}
