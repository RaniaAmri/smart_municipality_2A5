#include "employe.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
Employe::Employe()
{
id=0; salaire=0; nom=" "; prenom=""; date_de_naissance="";
}

Employe::Employe(int id,int salaire, QString nom, QString prenom, QString date_de_naissance)
{this->id=id;this->salaire=salaire; this->nom=nom; this->prenom=prenom; this->date_de_naissance=date_de_naissance;}
int Employe::getid(){return id;}
int Employe::getsalaire(){return salaire;}
QString Employe::getnom(){return  nom;}
QString Employe::getprenom(){return prenom;}
QString Employe::getdate(){return date_de_naissance;}
void Employe::setid(int id){this->id=id;}
void Employe::setsalaire(int salaire){this->salaire=salaire;}
void Employe::setnom(QString nom){this->nom=nom;}
void Employe::setprenom(QString prenom){this->prenom=prenom;}
void Employe::setdate(QString date_de_naissance){this->date_de_naissance=date_de_naissance;}
bool Employe::ajouter()
{

    QSqlQuery query;
  QString id_string= QString::number(id);
  QString id_salaire=QString::number(salaire);
         query.prepare("INSERT INTO employe (id, salaire, nom, prenom, date_de_naissance) "
                       "VALUES (:id,:salaire, :nom, :prenom, :date_de_naissance)");
         query.bindValue(":id",id_string);
         query.bindValue(":salaire",id_salaire);
         query.bindValue(":nom", nom);
         query.bindValue(":prenom", prenom);
         query.bindValue(":date_de_naissance",date_de_naissance);
        return query.exec();

}
bool Employe::supprimer(int id)
{
    QSqlQuery query;
         query.prepare(" Delete from employe where id=:id");
         query.bindValue(0, id);

        return query.exec();


}
QSqlQueryModel* Employe::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();


   model->setQuery("SELECT* FROM employe");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("salaire"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_de_naissance"));

  return  model;
}


bool Employe::modifier(int id, int salaire, QString nom, QString prenom,QString date_de_naissance)
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString sl= QString::number(salaire);
    query.prepare("update employe set nom=:nom,prenom=:prenom,salaire=:salaire,date_de_naissance=:date_de_naissance where id=:id");
    query.bindValue(":id", res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":salaire", sl);
    query.bindValue(":date_de_naissance",date_de_naissance);
    return query.exec();
}
QSqlQueryModel * Employe::rechercher (const QString &aux)

{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from employe where ((ID || NOM || PRENOM || SALAIRE || DATE_DE_NAISSANCE) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("prenom"));

    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_de_naissance"));

    return model;
}
QSqlQueryModel* Employe::trie()
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("select *FROM employe ORDER BY salaire ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("prenom"));

    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_de_naissaince"));

    return model;
}