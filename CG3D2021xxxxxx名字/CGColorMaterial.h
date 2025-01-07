#ifndef _CGColorMeterial_H_INCLUDED 
#define _CGColorMeterial_H_INCLUDED 
#include "CGRenderState.h" 
#include "Vector4.h" 

class CGColorMaterial : public CGRenderState
{
    DECLARE_SERIAL(CGColorMaterial)
public:
    CGColorMaterial();
    virtual ~CGColorMaterial() = default;
    //���л� 
    virtual void Serialize(CArchive& ar);
    virtual ERenderState type() const { return ERenderState::RS_Material; }
    //Ӧ�ã���д�����麯��ʵ�ֶ�̬ 
    virtual void apply(int index, const CG3DCamera* camera, CG3DRenderContext* ctx) const;

    //�������ݳ�Ա�������ø����������в��� 
    void setFlatColor(Vec4f color) {
        //setFrontAmbient(color);
        //setFrontDiffuse(color);
        //setFrontSpecular(color);
        setFrontEmission(color);
        //setBackAmbient(color);
        //setBackDiffuse(color);
        //setBackSpecular(color);
        setBackEmission(color);
    }
    void setShininess(float hininoss) { mFrontShininess = mBackShininess; }

    void setFrontAmbient(const Vec4f& color) { mFrontAmbient = color; }
    void setFrontDiffuse(const Vec4f& color) { mFrontDiffuse = color; }
    void setFrontSpecular(const Vec4f& color) {mFrontSpecular = color;}
    void setFrontEmission(const Vec4f& color) {mFrontEmission = color;}
    void setFrontShininess(float shininess) {mFrontShininess = shininess;}
    void setBackAmbient(const Vec4f& color) { mBackAmbient = color; }
    void setBackDiffuse(const Vec4f& color) { mBackDiffuse = color; }
    void setBackSpecular(const Vec4f& color) { mBackSpecular = color; }
    void setBackEmission(const Vec4f& color) { mBackEmission = color; }
    void setBackShininess(float shininess) { mBackShininess = shininess; }
     
    const Vec4f& frontAmbient() const {return mFrontAmbient; }
    const Vec4f& frontDiffuse() const {return mFrontDiffuse; }
    const Vec4f& frontSpecular()const { return mFrontSpecular;}
    const Vec4f& frontEmission() const { return mFrontEmission; }
    float frontShininess() const {  return mFrontShininess; }

    void setTransparency(float alpha);
    void setFrontTransparency(float alpha);
    void setBackTransparency(float alpha);

    // ��������
    //��������
    void setMetallicMaterial(Vec4f color = Vec4f(1,1,1,1)) {
        setFrontAmbient(Vec4f(0.25f, 0.25f, 0.25f, 1.0f) * color); // ΢���Ļ�����
        setFrontDiffuse(Vec4f(0.3f, 0.3f, 0.3f, 1.0f) * color);    // ��������
        setFrontSpecular(Vec4f(0.9f, 0.9f, 0.9f, 1.0f) * color); // ǿ���淴��
        setFrontShininess(76.8f); // �߹⻬��
        setFrontEmission(Vec4f(0.0f, 0.0f, 0.0f, 1.0f) * color);  // ���Է���
    }
    //���ϲ���
    void setPlasticMaterial(Vec4f color = Vec4f(1, 1, 1, 1)) {
        setFrontAmbient(Vec4f(0.2f, 0.2f, 0.2f, 1.0f) * color); // �޻�����
        setFrontDiffuse(Vec4f(0.8f, 0.8f, 0.8f, 1.0f) * color); // ��������
        setFrontSpecular(Vec4f(0.40f, 0.40f, 0.40f, 1.0f) * color); // ���еľ��淴��
        setFrontShininess(32.0f); // �еȹ⻬��
        setFrontEmission(Vec4f(0.0f, 0.0f, 0.0f, 1.0f) * color); // ���Է���
    }
    //��������
    void setGlassMaterial(Vec4f color = Vec4f(1, 1, 1, 1)) {
        setFrontAmbient(Vec4f(0.1f, 0.1f, 0.1f, 1.0f) * color);  // ��΢�����⣬ģ����Χ�����Բ�������΢Ӱ��
        setFrontDiffuse(Vec4f(0.6f, 0.6f, 0.6f, 0.5f) * color);  // �������䣬��͸���ȼ�����������ߴ�͸
        setFrontSpecular(Vec4f(0.98f, 0.98f, 0.98f, 1.0f) * color); // ��ǿ���淴��
        setFrontShininess(125.0f); // �߹⻬�ȱ��ֲ���
        setFrontEmission(Vec4f(0.0f, 0.0f, 0.0f, 1.0f) * color);    // ���Է���

        // ����������·���������͸���Ⱥ�������
        setFrontTransparency(0.9f);       // ���ø�͸����
        //setFrontRefractionIndex(1.5f);    // �����ĵ���������ԼΪ1.5
    }
    // ľ�ʲ���
    void setWoodenMaterial(Vec4f color = Vec4f(0.6f, 0.4f, 0.1f, 1.0f)) {
        setFrontAmbient(Vec4f(0.15f, 0.1f, 0.05f, 1.0f) * color); // ��ͻ�����
        setFrontDiffuse(Vec4f(0.6f, 0.4f, 0.1f, 1.0f) * color);   // ��ů��������
        setFrontSpecular(Vec4f(0.2f, 0.2f, 0.2f, 1.0f) * color); // �����ľ��淴�䣬ģ��ľ�ʹ���
        setFrontShininess(10.0f); // �ϵ͹⻬�ȣ�ľͷ����ϴֲ�
        setFrontEmission(Vec4f(0.0f, 0.0f, 0.0f, 1.0f));         // ���Է���
    }
    // �մɲ���
    void setCeramicMaterial(Vec4f color = Vec4f(1.0f, 1.0f, 1.0f, 1.0f)) {
        setFrontAmbient(Vec4f(0.1f, 0.1f, 0.1f, 1.0f) * color); // ������Ӱ���С
        setFrontDiffuse(Vec4f(0.8f, 0.8f, 0.8f, 1.0f) * color); // �������䣬�����մɵİ׾�
        setFrontSpecular(Vec4f(0.9f, 0.9f, 0.9f, 1.0f) * color); // ǿ���淴�䣬�մɵĹ����
        setFrontShininess(120.0f); // �ǳ��ߵĹ⻬�ȣ��մɱ���⻬
        setFrontEmission(Vec4f(0.0f, 0.0f, 0.0f, 1.0f));         // ���Է���
    }

    // �𽺲���
    void setRubberMaterial(Vec4f color = Vec4f(0.1f, 0.1f, 0.1f, 1.0f)) {
        setFrontAmbient(Vec4f(0.05f, 0.05f, 0.05f, 1.0f) * color); // �����Ļ����⣬��Ϊ������
        setFrontDiffuse(Vec4f(0.3f, 0.3f, 0.3f, 1.0f) * color);   // �������䣬�����ı���
        setFrontSpecular(Vec4f(0.2f, 0.2f, 0.2f, 1.0f) * color); // �����ľ��淴�䣬�𽺱��治����
        setFrontShininess(5.0f); // �͹⻬�ȣ����ָнϴֲ�
        setFrontEmission(Vec4f(0.0f, 0.0f, 0.0f, 1.0f));         // ���Է���
    }

    // ԭ��
    void setColorMaterial(EPolygonFace face, EColorMaterial color) {
        mColorMaterialFace = face;
        mColorMaterial = color;
    }
    EPolygonFace colorMaterialFace() const { return mColorMaterialFace; }
    EColorMaterial colorMaterial() const { return mColorMaterial; }
    void setColorMaterialEnabled(bool enabled) { mColorMaterialEnabled = enabled; }
    bool colorMaterialEnabled() const { return mColorMaterialEnabled; }

protected:
    Vec4f mFrontAmbient;    //ǰ���滷������ϵ����0~1�� 
    Vec4f mFrontDiffuse;    //ǰ����������ϵ����0~1�� 
    Vec4f mFrontSpecular;   //ǰ���澵�淴��ϵ����0~1�� 
    Vec4f mFrontEmission;   //ǰ����ɢ��ϵ����0~1�� 
    Vec4f mBackAmbient;     //�����滷������ϵ����0~1�� 
    Vec4f mBackDiffuse;     //������������ϵ����0~1�� 
    Vec4f mBackSpecular;    //�����澵�淴��ϵ����0~1�� 
    Vec4f mBackEmission;    //������ɢ��ϵ����0~1�� 
    float mBackShininess;   //������⻬ϵ����0~128�� 
    float mFrontShininess;  //ǰ����⻬ϵ����0~128�� 
    //��ɫ���ʣ����õ���ɫglColor��Ϊ���ʲ����� 
    EPolygonFace mColorMaterialFace;    //������������ 
    EColorMaterial mColorMaterial;      //��ɫ��Ϊ���ֲ��ʲ��� 
    bool mColorMaterialEnabled;         //������ɫ��Ϊ�������� 
};

#endif //_CGColorMeterial_H_INCLUDED
