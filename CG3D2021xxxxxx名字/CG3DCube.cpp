#include "pch.h" 
#include "CG3DCube.h" 
#include "CG3DRenderContext.h" 
#include "CG3DCamera.h" 

IMPLEMENT_SERIAL(CG3DCube, CG3DRenderable, 1)

CG3DCube::CG3DCube()
	: CG3DRenderable(CString("CG3DCube")), mSize(1)
{
	mName.Format(_T("立方体-%ld"), sID);
}
CG3DCube::CG3DCube(double size) //给定边长 
	: CG3DRenderable(CString("CG3DCube")), mSize(size)
{
	mName.Format(_T("立方体-%ld"), sID);
}

CG3DCube::CG3DCube(const CG3DCube& other)
	: CG3DRenderable(CString("CG3DCube")), mSize(other.mSize)
{
	mName.Format(_T("立方体-%ld"), sID);
}

CG3DCube::~CG3DCube()
{
}

//序列化 
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

//绘制函数，包括填充色和描边
void CG3DCube::Draw(bool outline) {
	double half = mSize / 2; //模型坐标系在正方体中心，边（面）与坐标轴平行 

	// 如果outline为true，则仅绘制黑色描边
	if (outline) {
		glColor3f(0.0f, 0.0f, 0.0f); // 设置颜色为黑色
	}
	else {
		// 以下为原始颜色设置
		glColor3f(0.992f, 0.996f, 0.024f); // 颜色改为黄色 #FDFE06
	}
	glVertex3f(half, half, -half);
	glVertex3f(-half, half, -half);
	glVertex3f(-half, half, half);
	glVertex3f(half, half, half);

	if (!outline) glColor3f(1.0f, 1.0f, 1.0f); // 颜色改成白色 #FFFFFF
	glVertex3f(half, -half, half);
	glVertex3f(-half, -half, half);
	glVertex3f(-half, -half, -half);
	glVertex3f(half, -half, -half);

	if (!outline) glColor3f(0.153f, 0.102f, 0.996f); // 颜色改为蓝色 #271AFE
	glVertex3f(half, half, half);
	glVertex3f(-half, half, half);
	glVertex3f(-half, -half, half);
	glVertex3f(half, -half, half);

	if (!outline) glColor3f(0.431f, 0.992f, 0.000f); // 颜色改成绿色 #6EFD00
	glVertex3f(half, -half, -half);
	glVertex3f(-half, -half, -half);
	glVertex3f(-half, half, -half);
	glVertex3f(half, half, -half);

	if (!outline) glColor3f(0.941f, 0.596f, 0.067f); // 颜色改成橙色 #F09811
	glVertex3f(-half, half, half);
	glVertex3f(-half, half, -half);
	glVertex3f(-half, -half, -half);
	glVertex3f(-half, -half, half);

	if (!outline) glColor3f(0.914f, 0.043f, 0.075f); // 颜色改成红色 #E90B13
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
	Draw(false); // 绘制填充色
	glEnd();

	// 添加描边
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(6.0f); // 设置线宽
	glBegin(GL_QUADS);
	Draw(true); // 绘制描边
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
	Draw(false); // 绘制填充色
	glEnd();

	// 添加描边
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(6.0f); // 设置线宽
	glBegin(GL_QUADS);
	Draw(true); // 绘制描边
	glEnd();

	glPopMatrix();
}

void CG3DCube::computeBoundingBox() //计算包围盒 
{
	mABox.setNull();  //先清空 
	//根据参数和矩阵计算包围盒 
	mABox = ABox3d(Vector3<double>(-mSize / 2, -mSize / 2, -mSize / 2), Vector3<double>(mSize / 2, mSize / 2, mSize / 2));
	setBoundsDirty(false);
}
