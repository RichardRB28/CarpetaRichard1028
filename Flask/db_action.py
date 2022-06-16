import boto3

dynamo_client=boto3.resource('dynamodb')
tabla=dynamo_client.Table('sensadodata')

def save_data(payload):
    response = tabla.put_item(
       Item = payload
    )
    return(response)

def get_all_data():
    response=tabla.scan()#escanea todos los datos de la tabla
    data=response['Items']
    return(data)
    #while 'LastEvaluatedKey' in response:
        #response=tabla.scan(ExclusiveStarkey=response['LastEvaluatedKey'])
        #data.extend(response['Items'])



